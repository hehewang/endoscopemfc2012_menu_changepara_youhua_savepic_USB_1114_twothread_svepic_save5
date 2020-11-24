
/*
 * COM���ڲ�������ص�Э�����
 * �ļ�����: .cpp�ļ�
 */
#include "pch.h"
#include "ProcessCard.h"
#include <algorithm>
#include <afxtempl.h>
#include <vector>
#include <sys/timeb.h>
#include <fstream>
#include<iostream>
using namespace std;

CProcessCard::CProcessCard(void)
{
	// ��ʼ��
	m_hCom = INVALID_HANDLE_VALUE;
	m_nBaudRate = CBR_9600; // ��ʼ��������
	m_bExitFlag = TRUE;
	m_comThread = NULL;
	m_pDataHandler = NULL;
}


CProcessCard::~CProcessCard(void)
{
	Release();
}




bool CProcessCard::Initialize(CString comName, int nBaudRate)
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
	/*tmpTheApp->*/m_comThread = AfxBeginThread(CProcessCard::RecvHandler, this, THREAD_PRIORITY_HIGHEST);
	m_bExitFlag = FALSE;

	return true;
}

// �ͷŴ���
void CProcessCard::Release()
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
BOOL CProcessCard::SendData(BYTE* buf, int size)
{	
	/*int nWriteLog = GetPrivateProfileInt("CFG","WriteLog",0,"testBitmap.ini");
	if ( 1 == nWriteLog )
	{
	CString sLog;
	sLog.Format("-----------------------------------------------------CurB:%03d,F:%03d,E:%02d,V:%02d,N:%d",g_nAvg,g_nPeek,g_nExposure,buf[5],999);
	WriteLog(sLog);
	}*/
	;
	if (m_bExitFlag)
	{
		return FALSE;
	}
	DWORD dwWrite = 0;

	BOOL RTN = FALSE;
	try
	{
		RTN = WriteFile(m_hCom, (LPCVOID)buf, size, &dwWrite, NULL);
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
UINT CProcessCard::RecvHandler(LPVOID lpParam)
{
	return ((CProcessCard*)(lpParam))->OnRecv(lpParam);
}
UINT CProcessCard::GetBytesInCOM()
{
	DWORD dwError = 0;  /** ������ */
	COMSTAT  comstat;   /** COMSTAT�ṹ��,��¼ͨ���豸��״̬��Ϣ */
	memset(&comstat, 0, sizeof(COMSTAT));

	UINT BytesInQue = 0;
	/** �ڵ���ReadFile��WriteFile֮ǰ,ͨ�������������ǰ�����Ĵ����־ */
	if (ClearCommError(m_hCom, &dwError, &comstat))
	{
		BytesInQue = comstat.cbInQue; /** ��ȡ�����뻺�����е��ֽ��� */
	}

	return BytesInQue;
}

// �����յ���������ʱ
UINT CProcessCard::OnRecv(LPVOID lpParam)
{
	CProcessCard* pCom =(CProcessCard*)lpParam;
	DWORD dwSize=0;
	BOOL bRet = TRUE;
	//BYTE buf[32] = {0};
	//CString dbgbuf,dbgtemp;
	//char testdat[]="";
	while (1) 
	{	char testdata=0;
		dwSize = 0;
		UINT BytesInQue = pCom->GetBytesInCOM();
		do
		{
			bRet = ReadFile(m_hCom,			  // ���ھ��
						&m_rBuf, // ����
						1,				  // ���һ�ζ����ڲ�����Ҫ�������ֽ�������
						&dwSize,	      // ���һ�ζ����ڲ�����ʵ�ʶ������ֽ�����
						NULL );
					// ������Ч���رմ��ھ��˳����߳�
			if(!bRet)
				return 0;
			if(dwSize > 0)
			{
				//cout<<m_rBuf;
			}


		}while(--BytesInQue);
		// �����������
	}
	return 1;
}

