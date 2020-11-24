/*
* COM���ڲ���
* �ļ�����: .h�ļ�
*/
#ifndef __LIGHTCOMIO_H__
#define __LIGHTCOMIO_H__

// COM����ͨ����

#include "datatype.h"


unsigned short GetCrc(const unsigned char *pszbuf,int len);

class CLightComIO 
{
public:
	CLightComIO();
	virtual ~CLightComIO();

public:

	// ��ʼ��COM
	bool Initialize(CString comName, int nBaudRate);

	// �ͷ�COM
	void Release();

	// ���ݷ���
	BOOL SendData(BYTE* buf, int size);

	// ���ڽ������ݼ���߳�
	static UINT RecvHandler( LPVOID lpParam );

	// �����յ���������ʱ
	UINT OnRecv(LPVOID lpParam);

	//�߳��˳���ʶ
	bool m_bExitFlag;

	void SetDataHandler( CComDataHandler* p )
	{
		m_pDataHandler = p;
	}

protected:
	HANDLE m_hCom;   // ���ھ��
	CWinThread* m_comThread;
	int m_nBaudRate; // ������

	// �Ѿ���ȡ�����ݸ���
	DWORD m_rSize;

	// ������
	BYTE m_rBuf[32];

	CComDataHandler* m_pDataHandler;
};

#endif
