/*
 * COM���ڲ�������ص�Э�����
 * �ļ�����: .cpp�ļ�
 */

#include "pch.h"
#include "VideoComIO.h"
#include <algorithm>
#include <afxtempl.h>
#include <vector>
#include <sys/timeb.h>
#include <fstream>

using namespace std;

//CVideoComIO g_com;
//CWinThread* g_m_comThread;
//HANDLE g_hCom;   // ���ھ��
/*std::vector<CRetryInfo> g_RetryList;*/


CVideoComIO::CVideoComIO()
{
	// ��ʼ��
	m_hCom = INVALID_HANDLE_VALUE;
	m_nBaudRate = CBR_9600; // ��ʼ��������
	m_bExitFlag = TRUE;
	m_comThread = NULL;
	m_pDataHandler = NULL;
}

CVideoComIO::~CVideoComIO()
{
	Release();
}

bool CVideoComIO::Initialize(CString comName, int nBaudRate)
{

	// ��ʼ������
	m_rSize = 0;
	memset(m_rBuf, 0, sizeof(m_rBuf));

	// �򿪴���
	m_hCom = CreateFile(comName,
						GENERIC_READ | GENERIC_WRITE,
						0,    // Exclusive access 
						NULL, // No security attributes 
						OPEN_EXISTING,
						0,    // FILE_FLAG_OVERLAPPED
						NULL);
	if (m_hCom == INVALID_HANDLE_VALUE) {
		// ��ʧ��
//		AfxMessageBox(_T("��COMʧ��"));
		return false;
	}

	if(nBaudRate>0) {
		// ���ñ�����
		m_nBaudRate = nBaudRate;
	}

	// ȡ��ָ�����ڵĵ�ǰ״̬
	DCB dcb;
	if(!GetCommState(m_hCom,(LPDCB)&dcb)) {
		return false;
	}

	dcb.BaudRate = (DWORD)m_nBaudRate;
	dcb.ByteSize = 8;
	dcb.Parity = NOPARITY;
	dcb.StopBits = ONESTOPBIT;
	dcb.fBinary = 1;

	// ����ָ������״̬
	if(!SetCommState(m_hCom, &dcb)) {
		LPVOID lpMsgBuf;
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | 
					  FORMAT_MESSAGE_FROM_SYSTEM | 
					  FORMAT_MESSAGE_IGNORE_INSERTS,
					  NULL,
					  GetLastError(),
					  0, 
					  (LPTSTR)&lpMsgBuf,
					  0,
					  NULL);
		MessageBox(NULL, (LPCTSTR)lpMsgBuf, _T("Error"), MB_OK | MB_ICONINFORMATION);
		LocalFree(lpMsgBuf);
		return false;
	}
	
	// ���ó�ʱ
	COMMTIMEOUTS timeouts;
	timeouts.ReadIntervalTimeout			= MAXDWORD; // �������ʱ
	timeouts.ReadTotalTimeoutMultiplier		= 0; // ��ʱ��ϵ��
	timeouts.ReadTotalTimeoutConstant		= 0; // ��ʱ�䳣��
	timeouts.WriteTotalTimeoutMultiplier	= 0; // дʱ��ϵ��
	timeouts.WriteTotalTimeoutConstant		= 1000; // дʱ�䳣��(1���д��ʱ)

	if (!SetCommTimeouts(m_hCom, &timeouts)) {
		// ���ó�ʱʧ��
		return false;
	}

	// ���ô��ڶ������д����Ĵ�С
	SetupComm(m_hCom, 1024*4, 512*4);

	// ��մ��ڶ�д������
	PurgeComm(m_hCom, PURGE_RXCLEAR | PURGE_TXCLEAR);

	// �����߳�
	/*tmpTheApp->*/m_comThread = AfxBeginThread(CVideoComIO::RecvHandler, this, THREAD_PRIORITY_HIGHEST);
	m_bExitFlag = FALSE;

	return true;
}

// �ͷŴ���
void CVideoComIO::Release()
{	
	if(!m_bExitFlag)
	{
		m_bExitFlag = TRUE;
		::WaitForSingleObject(m_comThread->m_hThread,10);
	}
	if(m_hCom != INVALID_HANDLE_VALUE) 
	{
		CloseHandle(m_hCom);
		m_hCom = INVALID_HANDLE_VALUE;
	}

}

// ���ݷ���
BOOL CVideoComIO::SendData(BYTE* buf, int size)
{	
	/*int nWriteLog = GetPrivateProfileInt("CFG","WriteLog",0,"testBitmap.ini");
	if ( 1 == nWriteLog )
	{
	CString sLog;
	sLog.Format("-----------------------------------------------------CurB:%03d,F:%03d,E:%02d,V:%02d,N:%d",g_nAvg,g_nPeek,g_nExposure,buf[5],999);
	WriteLog(sLog);
	}*/
	if (m_bExitFlag)
	{
		return FALSE;
	}
	DWORD dwWrite = 0;
	//��ӷ���Э��
	BYTE* pBuf;
	
	//����(��������λ֡ͷ)
	WORD sndsize = size;
	
	BYTE sndBuf[32];
	memset(sndBuf, 0, sizeof(sndBuf));
	pBuf = sndBuf;
	
	//֡��ʼ
	*(BYTE*)pBuf = 0xA5;
	pBuf++;
	*(BYTE*)pBuf = 0x5A;
	pBuf++;

	for( int i=0; i<sndsize; i++)
	{
		*(BYTE*)pBuf = buf[i];
		pBuf++;		
	}
 	//֡����
// 	*(BYTE*)pBuf = 0x97;
// 	pBuf++;
// 	*(BYTE*)pBuf = 0x98;
// 	pBuf++;
	BOOL RTN = FALSE;
	try
	{
		RTN = WriteFile(m_hCom, (LPCVOID)sndBuf, sndsize+2, &dwWrite, NULL);
	}
	catch (CMemoryException* e)
	{
		
	}
	catch (CFileException* e)
	{
	}
	catch (CException* e)
	{
	}

	//���log���룬ʵ�ʷ���ʱ����
	/*
	CString cstemp;
	CString csbuf;
	for(int j = 0; j<(pBuf-sndBuf); j++)
	{
		cstemp.Format(_T("%02X "),(unsigned char)sndBuf[j]);
		csbuf = csbuf + cstemp;
	}
	
	TRACE(csbuf);	
	CString filePath;
	filePath = ReturnPath();
	filePath += "\\Voice\\SendCOMLOG.txt";
	WriteComLog(csbuf,filePath);*/
	
	return RTN;
}

// ���ڽ��ռ���߳�
UINT CVideoComIO::RecvHandler(LPVOID lpParam)
{
	return ((CVideoComIO*)(lpParam))->OnRecv(lpParam);
}

// �����յ���������ʱ
UINT CVideoComIO::OnRecv(LPVOID lpParam)
{
	CVideoComIO* pCom =(CVideoComIO*)lpParam;
	DWORD dwSize=0;
	BOOL bRet = TRUE;
	BYTE buf[32] = {0};
	CString dbgbuf,dbgtemp;

	while (1) 
	{		
		dwSize = 0;
 		bRet = ReadFile(m_hCom,			  // ���ھ��
						m_rBuf + m_rSize, // ����
						1,				  // ���һ�ζ����ڲ�����Ҫ�������ֽ�������
						&dwSize,	      // ���һ�ζ����ڲ�����ʵ�ʶ������ֽ�����
						NULL );


		// ������Ч���رմ��ھ��˳����߳�
		if(!bRet) {
			return 0;
		}

		// �����������
		if(dwSize > 0) 
		{
			m_rSize += dwSize;
		
			//�����ʼλA55A
			if( m_rSize==1 )
			{
				if(m_rBuf[0] != 0xA5 )
				{
					//�ѽ�����λ����
					m_rSize = 0;
					//��BUF
					memset(m_rBuf,0,sizeof(m_rBuf));
				}
			}
			
			if(m_rSize==2)
			{
				if(m_rBuf[1] != 0x5A )
				{
					m_rSize = 0;
					memset(m_rBuf,0,sizeof(m_rBuf));
				}
			}

			//����ָ������֡
			if( m_rBuf[2]==(m_rSize-3) )
			{					
				for( int j = 0; j < m_rSize ; j++ )
				{
					buf[j] = m_rBuf[j];
				}

				//�������ڷ�����Ϣ
				if ( m_pDataHandler )
					m_pDataHandler->ProcessData(buf,m_rSize);

				m_rSize = 0;
				memset(m_rBuf,0,sizeof(m_rBuf));


				//���log���룬ʵ�ʷ���ʱ����
				/*dbgbuf.Empty();
				dbgtemp.Empty();
				for(int x = 0; x < j+2; x++)
				{
					dbgtemp.Format(_T("%02X "),buf[x]);
					dbgbuf = dbgbuf + dbgtemp;
				}
				CString filePath;
				filePath = ReturnPath();
				filePath += "\\Voice\\COMLOG.txt";
				WriteComLog(dbgbuf,filePath);
				TRACE(dbgbuf);*/
				//��������					
				memset(buf,0,32);	
			}


			//���ճ���̫������������
			if( m_rSize>=64 )
			{
				m_rSize=0;
				memset(m_rBuf, 0, sizeof(m_rBuf));
			}
		}
		// û�ж�������
		else {
			Sleep(1);
		}
	}
	return 1;
}

