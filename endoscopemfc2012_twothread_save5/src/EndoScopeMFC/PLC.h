#pragma once
#include "DataType.h"
#include "VideoComIO.h"
#include "LightComIO.h"
#include "ProcessCard.h"
#include <iostream>

#define WM_SERIALPORT_MSG		WM_USER+100


class CPLC :
	public CComDataHandler
{
public:
	CPLC(void);
	virtual ~CPLC(void);
private:
	bool m_bRegister;				//�յ���λ����һ�������ظ�

	CString m_strSemState;		    //�뵼��״̬
public:
	//��Ƶ���ڳ�ʼ��
	bool VideoInitialize( CString strCOM, int nBaudRate );

	//���Դ���ڳ�ʼ��
	bool LightInitialize( CString strCOM, int nBaudRate );

	//ͼ����崮�ڳ�ʼ��
	bool ProcessCardInitialize(CString strCOM, int nBaudRate );

	//������յ��Ĵ�������
	void ProcessData( unsigned char* pBuf, int size );

	//��ȡ����λ������״̬
	bool GetRegState(){	return m_bRegister; }

	//��ȡ\���ð뵼��״̬
	CString GetSemState(){ return m_strSemState; }
	void SetSemState( CString strSem ){ m_strSemState = strSem; }

	//����
	BOOL KeepAlive()
	{
		BYTE bBuf[2] = { 0x06, 0xA1 };
		return m_VideoComIO.SendData(bBuf,2);
	}

	//����������
	BOOL OpenBuzzer()
	{
		BYTE bBuf[3] = { 0x07, 0xB1, 0x00 };
		return m_VideoComIO.SendData( bBuf, 3 );
	}
	////�ھ��ͺ�
	//BOOL EndoscopicModel()
	//{
	//	//BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0x31, 0x00, 0x01};
	//	return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	//}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////¼�벡����Ϣ
	//����¼��
	BOOL NowEnter()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0x31, 0x00, 0x01};
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	//¼�����
	BOOL OverEnter()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0x31, 0x00, 0x00};
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	//׼������
	BOOL ReadyEnter()
	{
		BYTE bBuf[ 14 ] = {0x0D, 0x82, 0x00, 0x31, 0xD7, 0xBC, 0xB1, 0xB8, 0xBE, 0xCD, 0xD0, 0xF8, 0xFF, 0xFF};
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////¼��
	//����¼��
	BOOL NowVideo()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0x33, 0x00, 0x03};
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	//ֹͣ¼��
	BOOL StopVideo()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0x33, 0x00, 0x02};
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	//׼��¼��
	BOOL ReadyVideo()
	{
		BYTE bBuf[ 14 ] = {0x0D, 0x82, 0x00, 0x41, 0xD7, 0xBC, 0xB1, 0xB8, 0xBE, 0xCD, 0xD0, 0xF8, 0xFF, 0xFF};
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////�洢���ⲿ�豸
	//���ڴ洢
	BOOL NowSave()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0x35, 0x00, 0x05};
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	//ֹͣ�洢
	BOOL StopSave()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0x35, 0x00, 0x04};
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	//�洢���
	BOOL OverSave()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0x35, 0x00, 0x04};
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	//δ��������
	BOOL NotLink()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0x35, 0x00, 0x06};
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	//�����Ѳ���
	BOOL AlreadyLink()
	{
		BYTE bBuf[ 16 ] = {0x0F, 0x82, 0x00, 0x51, 0xCD, 0xE2, 0xC9, 0xE8, 0xD2, 0xD1, 0xB2, 0xE5, 0xC8, 0xEB, 0xFF, 0xFF};
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	//�����Ѳ���
	BOOL ReadySave()
	{
		BYTE bBuf[ 14 ] = {0x0D, 0x82, 0x00, 0x51, 0xD7, 0xBC, 0xB1, 0xB8, 0xBE, 0xCD, 0xD0, 0xF8, 0xFF, 0xFF};
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////��ӡ
	//���ڴ�ӡ
	BOOL NowPrint()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0x37, 0x00, 0x08};
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	//ֹͣ��ӡ
	BOOL StopPrint()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0x37, 0x00, 0x07};
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	//��ӡ���
	BOOL OverPrint()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0x37, 0x00, 0x07};
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	//��ӡ��δ����
	BOOL NotLinkPrint()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0x37, 0x00, 0x09};
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	//׼������
	BOOL ReadyPrint()
	{
		BYTE bBuf[ 14 ] = {0x0D, 0x82, 0x00, 0x61, 0xD7, 0xBC, 0xB1, 0xB8, 0xBE, 0xCD, 0xD0, 0xF8, 0xFF, 0xFF};
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////���ģʽ
	//ƽ�����
	BOOL AverageMetering()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0x02, 0x00, 0x00};
		 m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
		BYTE Buf[15]={0xFF,0xAA,0x03,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
		return m_ProcessCardComIO.SendData(Buf,sizeof(Buf)/sizeof(Buf[0]));
	}
	//��ֵ���
	BOOL PeakMetering()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0x02, 0x00, 0x01};
		 m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
		BYTE Buf[15]={0xFF,0xAA,0x03,0x03,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
		return m_ProcessCardComIO.SendData(Buf,sizeof(Buf)/sizeof(Buf[0]));
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////Bֵ����
	BOOL B( int nVal )
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0x91, 0x00, 0x00};
		BYTE buf[15] = { 0xFF,0xAA,0x03,0x02,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
		//int temp = nVal + 5;
		buf[7] =(BYTE)(nVal+0x37);
		m_ProcessCardComIO.SendData(buf, sizeof(buf) / sizeof(buf[0]));
		if ( nVal >= 0 )
		{
			bBuf[5] = (BYTE)nVal;
		}
		else
		{
			bBuf[4] = 0xFF;
			bBuf[5] = (BYTE)(0xFF + nVal + 1);
		}
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////Rֵ����
	BOOL R( int nVal )
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0x95, 0x00, 0x00};
		BYTE buf[15] = { 0xFF,0xAA,0x03,0x02,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
		//int temp = nVal + 5;
		buf[7] = (BYTE)(nVal+0x37);
		m_ProcessCardComIO.SendData(buf, sizeof(buf) / sizeof(buf[0]));
		if ( nVal >= 0 )
		{
			bBuf[5] = (BYTE)nVal;
		}
		else
		{
			bBuf[4] = 0xFF;
			bBuf[5] = (BYTE)(0xFF + nVal + 1);
		}
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////ͼ��Ŵ�
	BOOL Zoom_Card1()//�Ŵ�1��
	{
		BYTE bBuf[ 15 ] = {0xFF, 0xAA, 0x03, 0x06, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
		return m_ProcessCardComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	BOOL Zoom_Card2()//�Ŵ�2��
	{
		BYTE bBuf[ 15 ] = {0xFF, 0xAA, 0x03, 0x06, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
		return m_ProcessCardComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	//�Ŵ�1��
	BOOL Zoom1()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x11, 0x01, 0x00, 0x0A};
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	//�Ŵ�1.2��
	BOOL Zoom2()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x11, 0x01, 0x00, 0x0C};
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	//�Ŵ�1.5��
	BOOL Zoom3()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x11, 0x01, 0x00, 0x0F};
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	//�Ŵ�2��
	BOOL Zoom4()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x11, 0x01, 0x00, 0x14};
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////�����趨
	//����Բ��
	BOOL SetCircular()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0x06, 0x00, 0x00};
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	//���÷���
	BOOL SetSquare()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0x06, 0x00, 0x01};
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////���Դ����
	//���Դ��
	BOOL OpenLight()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0x71, 0x00, 0x01};
#ifdef _LPort
		return m_LightComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
#else
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
#endif
	}
	//���Դ��
	BOOL CloseLight()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0x71, 0x00, 0x00};
#ifdef _LPort
		return m_LightComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
#else
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
#endif
	}
	BOOL Light( int nVal )
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0x21, 0x00, 0x00};
		bBuf[5] = (BYTE)nVal;
#ifdef _LPort
		return m_LightComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
#else
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
#endif
	}
	//��Դ�Զ���
	BOOL OpenAuto()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0x25, 0x00, 0x01};
#ifdef _LPort
		return m_LightComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
#else
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
#endif
	}
	//��Դ�Զ���
	BOOL CloseAuto()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0x25, 0x00, 0x00};
#ifdef _LPort
		return m_LightComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
#else
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
#endif
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////�����ȵ���
	BOOL Clarity( int nVal )
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0xA0, 0x00, 0x00};
		bBuf[5] = (BYTE)nVal;
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////���ȵ���
	//����0��
	BOOL Brightness0()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0xA1, 0x00, 0x00};
		BYTE buf[15] = { 0xFF, 0xAA, 0x03, 0x0C, 0x00,0x00,0x00,0x3C,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
		m_ProcessCardComIO.SendData(buf, sizeof(buf) / sizeof(buf[0]));

		Sleep(5);
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	//����1��
	BOOL Brightness1()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0xA1, 0x00, 0x01};
		BYTE buf[15] = { 0xFF, 0xAA, 0x03, 0x0C, 0x00,0x00,0x00,0x3D,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
		m_ProcessCardComIO.SendData(buf, sizeof(buf) / sizeof(buf[0]));
		Sleep(5);

		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	//����2��
	BOOL Brightness2()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0xA1, 0x00, 0x02};
		BYTE buf[15] = { 0xFF, 0xAA, 0x03, 0x0C, 0x00,0x00,0x00,0x3E,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
		m_ProcessCardComIO.SendData(buf, sizeof(buf) / sizeof(buf[0]));
		Sleep(5);
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	//����3��
	BOOL Brightness3()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0xA1, 0x00, 0x03};
		BYTE buf[15] = { 0xFF, 0xAA, 0x03, 0x0C, 0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
		m_ProcessCardComIO.SendData(buf, sizeof(buf) / sizeof(buf[0]));
		Sleep(5);

		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	//����4��
	BOOL Brightness4()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0xA1, 0x00, 0x04};
		BYTE buf[15] = { 0xFF, 0xAA, 0x03, 0x0C, 0x00,0x00,0x00,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
		m_ProcessCardComIO.SendData(buf, sizeof(buf) / sizeof(buf[0]));
		Sleep(5);
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	//����5��
	BOOL Brightness5()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0xA1, 0x00, 0x05};
		BYTE buf[15] = { 0xFF, 0xAA, 0x03, 0x0C, 0x00,0x00,0x00,0x41,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
		 m_ProcessCardComIO.SendData(buf, sizeof(buf) / sizeof(buf[0]));
		 Sleep(5);
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	//����6��
	BOOL Brightness6()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0xA1, 0x00, 0x06};

		BYTE buf[15] = { 0xFF, 0xAA, 0x03, 0x0C, 0x00,0x00,0x00,0x42,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
		m_ProcessCardComIO.SendData(buf, sizeof(buf) / sizeof(buf[0]));
		Sleep(5);
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	//����7��
	BOOL Brightness7()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0xA1, 0x00, 0x07};
		BYTE buf[15] = { 0xFF, 0xAA, 0x03, 0x0C, 0x00,0x00,0x00,0x43,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
		m_ProcessCardComIO.SendData(buf, sizeof(buf) / sizeof(buf[0]));
		Sleep(5);
		 return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	//����8��
	BOOL Brightness8()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0xA1, 0x00, 0x08};
		BYTE buf[15] = { 0xFF, 0xAA, 0x03, 0x0C, 0x00,0x00,0x00,0x44,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
		m_ProcessCardComIO.SendData(buf, sizeof(buf) / sizeof(buf[0]));
		Sleep(5);
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	//����9��
	BOOL Brightness9()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0xA1, 0x00, 0x09};
		BYTE buf[15] = { 0xFF, 0xAA, 0x03, 0x0C, 0x00,0x00,0x00,0x45,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
		m_ProcessCardComIO.SendData(buf, sizeof(buf) / sizeof(buf[0]));
		Sleep(5);
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	//����10��
	BOOL Brightness10()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0xA1, 0x00, 0x0A};
		BYTE buf[15] = { 0xFF, 0xAA, 0x03, 0x0C, 0x00,0x00,0x00,0x46,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
		m_ProcessCardComIO.SendData(buf, sizeof(buf) / sizeof(buf[0]));
		Sleep(5);
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	//����-1��
	BOOL Brightness11()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0xA1, 0xFF, 0xFF};
		BYTE buf[15] = { 0xFF, 0xAA, 0x03, 0x0C, 0x00,0x00,0x00,0x3B,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
		return m_ProcessCardComIO.SendData(buf, sizeof(buf) / sizeof(buf[0]));
		Sleep(5);
		 m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	//����-2��
	BOOL Brightness12()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0xA1, 0xFF, 0xFE};
		BYTE buf[15] = { 0xFF, 0xAA, 0x03, 0x0C, 0x00,0x00,0x00,0x3A,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
		return m_ProcessCardComIO.SendData(buf, sizeof(buf) / sizeof(buf[0]));
		Sleep(5);
		 m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	//����-3��
	BOOL Brightness13()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0xA1, 0xFF, 0xFD};
		BYTE buf[15] = { 0xFF, 0xAA, 0x03, 0x0C, 0x00,0x00,0x00,0x39,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
		 m_ProcessCardComIO.SendData(buf, sizeof(buf) / sizeof(buf[0]));
		 Sleep(5);
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	//����-4��
	BOOL Brightness14()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0xA1, 0xFF, 0xFC};
		BYTE buf[15] = { 0xFF, 0xAA, 0x03, 0x0C, 0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
		 m_ProcessCardComIO.SendData(buf, sizeof(buf) / sizeof(buf[0]));
		 Sleep(5);
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	//����-5��
	BOOL Brightness15()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0xA1, 0xFF, 0xFB};
		BYTE buf[15] = { 0xFF, 0xAA, 0x03, 0x0C, 0x00,0x00,0x00,0x37,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
		 m_ProcessCardComIO.SendData(buf, sizeof(buf) / sizeof(buf[0]));
		 Sleep(5);
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	//����-6��
	BOOL Brightness16()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0xA1, 0xFF, 0xFA};
		BYTE buf[15] = { 0xFF, 0xAA, 0x03, 0x0C, 0x00,0x00,0x00,0x36,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
		 m_ProcessCardComIO.SendData(buf, sizeof(buf) / sizeof(buf[0]));
		 Sleep(5);
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	//����-7��
	BOOL Brightness17()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0xA1, 0xFF, 0xF9};
		BYTE buf[15] = { 0xFF, 0xAA, 0x03, 0x0C, 0x00,0x00,0x00,0x35,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
		 m_ProcessCardComIO.SendData(buf, sizeof(buf) / sizeof(buf[0]));
		 Sleep(5);
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	//����-8��
	BOOL Brightness18()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0xA1, 0xFF, 0xF8};
		BYTE buf[15] = { 0xFF, 0xAA, 0x03, 0x0C, 0x00,0x00,0x00,0x34,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
		 m_ProcessCardComIO.SendData(buf, sizeof(buf) / sizeof(buf[0]));
		 Sleep(5);
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	//����-9��
	BOOL Brightness19()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0xA1, 0xFF, 0xF7};
		BYTE buf[15] = { 0xFF, 0xAA, 0x03, 0x0C, 0x00,0x00,0x00,0x33,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
		 m_ProcessCardComIO.SendData(buf, sizeof(buf) / sizeof(buf[0]));
		 Sleep(5);
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	//����-10��
	BOOL Brightness20()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0xA1, 0xFF, 0xF6};
		BYTE buf[15] = { 0xFF, 0xAA, 0x03, 0x0C, 0x00,0x00,0x00,0x32,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
		 m_ProcessCardComIO.SendData(buf, sizeof(buf) / sizeof(buf[0]));
		 Sleep(5);
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////�Աȶȵ���
	BOOL Contrast( int nVal )
	{
		BYTE buf[15] = { 0xFF, 0xAA, 0x03, 0x0D, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
		buf[7] = (BYTE)(nVal+5);
		m_ProcessCardComIO.SendData(buf, sizeof(buf) / sizeof(buf[0]));
		Sleep(5);
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0xA2, 0x00, 0x00};
		bBuf[5] = (BYTE)nVal;
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////���Ͷȵ���
	BOOL Saturation( int nVal )
	{
		BYTE buf[15] = { 0xFF, 0xAA, 0x03, 0x02, 0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
		//buf[7] = nVal*10;
		int temp = nVal+60;
		buf[7] = (BYTE)temp;
		m_ProcessCardComIO.SendData(buf, sizeof(buf) / sizeof(buf[0]));
		Sleep(5);
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0xA3, 0x00, 0x00};
		bBuf[5] = (BYTE)nVal;
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////�ع����
	//�ع�0��
	BOOL Exposure0()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0xA4, 0x00, 0x00};
		//BYTE buf[15] = { 0xFF, 0xAA, 0x03, 0x0C, 0x00,0x00,0x00,0x64,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
		
		BYTE buf[15] = { 0xFF, 0xAA, 0x03, 0x05, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
		buf[7] = 0;
		 m_ProcessCardComIO.SendData(buf, sizeof(buf) / sizeof(buf[0]));
		 Sleep(5);
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	//�ع�-1��
	BOOL Exposure1()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0xA4, 0xFF, 0xFF};
		BYTE buf[15] = { 0xFF, 0xAA, 0x03, 0x05, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
		buf[7] = 0x01;
		 m_ProcessCardComIO.SendData(buf, sizeof(buf) / sizeof(buf[0]));
		 Sleep(5);
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	//�ع�-2��
	BOOL Exposure2()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0xA4, 0xFF, 0xFE};
		BYTE buf[15] = { 0xFF, 0xAA, 0x03, 0x05, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
		buf[7] = 0x02;
		 m_ProcessCardComIO.SendData(buf, sizeof(buf) / sizeof(buf[0]));
		 Sleep(5);
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	//�ع�-3��
	BOOL Exposure3()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0xA4, 0xFF, 0xFD};
		BYTE buf[15] = { 0xFF, 0xAA, 0x03, 0x05, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
		buf[7] = 0x03;
		 m_ProcessCardComIO.SendData(buf, sizeof(buf) / sizeof(buf[0]));
		 Sleep(5);
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	//�ع�-4��
	BOOL Exposure4()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0xA4, 0xFF, 0xFC};
		BYTE buf[15] = { 0xFF, 0xAA, 0x03, 0x05, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
		buf[7] = 0x04;
		 m_ProcessCardComIO.SendData(buf, sizeof(buf) / sizeof(buf[0]));
		 Sleep(5);
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	//�ع�-5��
	BOOL Exposure5()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0xA4, 0xFF, 0xFB};
		BYTE buf[15] = { 0xFF, 0xAA, 0x03, 0x05, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
		buf[7] = 0x05;
		 m_ProcessCardComIO.SendData(buf, sizeof(buf) / sizeof(buf[0]));
		 Sleep(5);
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	//�ع�-6��
	BOOL Exposure6()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0xA4, 0xFF, 0xFA};
		BYTE buf[15] = { 0xFF, 0xAA, 0x03, 0x05, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
		buf[7] = 0x06;
		 m_ProcessCardComIO.SendData(buf, sizeof(buf) / sizeof(buf[0]));
		 Sleep(5);
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	//�ع�-7��
	BOOL Exposure7()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0xA4, 0xFF, 0xF9};
		BYTE buf[15] = { 0xFF, 0xAA, 0x03, 0x05, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
		buf[7] = 0x07;
		 m_ProcessCardComIO.SendData(buf, sizeof(buf) / sizeof(buf[0]));
		 Sleep(5);
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	//�ع�-8��
	BOOL Exposure8()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0xA4, 0xFF, 0xF8};
		BYTE buf[15] = { 0xFF, 0xAA, 0x03, 0x05, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
		buf[7] = 0x08;
		 m_ProcessCardComIO.SendData(buf, sizeof(buf) / sizeof(buf[0]));
		 Sleep(5);
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	//�ع�-9��
	BOOL Exposure9()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0xA4, 0xFF, 0xF7};
		BYTE buf[15] = { 0xFF, 0xAA, 0x03, 0x05, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
		buf[7] = 0x09;
		 m_ProcessCardComIO.SendData(buf, sizeof(buf) / sizeof(buf[0]));
		 Sleep(5);
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	//�ع�-10��
	BOOL Exposure10()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0xA4, 0xFF, 0xF6};
		BYTE buf[15] = { 0xFF, 0xAA, 0x03, 0x05, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
		buf[7] = 0x0A;
		 m_ProcessCardComIO.SendData(buf, sizeof(buf) / sizeof(buf[0]));
		 Sleep(5);
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	//��ȵ��ڣ���Χ0-10
	BOOL Sharpness(int val)
	{
		BYTE bBuf[8] = { 0xA5, 0x5A, 0x05, 0x82, 0x00, 0xA0, 0x00, 0x00};
		bBuf[7] = val;
		m_VideoComIO.SendData(bBuf, sizeof(bBuf) / sizeof(bBuf[0]));
		Sleep(5);
		BYTE buf[15]= { 0xFF, 0xAA, 0x03, 0x05, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
		buf[7] = val;
		return m_ProcessCardComIO.SendData(buf, sizeof(buf) / sizeof(buf[0]));

	}
	//�Զ��ع⿪
	BOOL ExposureOpen()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0xA6, 0x00, 00};
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	//�Զ��ع⿪
	BOOL ExposureClose()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0xA6, 0x00, 01};
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////�������
	BOOL Gain( int nVal )
	{
		//std::cout<<"Gain:"<<nVal<<endl;
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0xA5, 0x00, 0x00};
		bBuf[5] = (BYTE)nVal;
		 m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
		 Sleep(5);
		BYTE buf[ 15 ] = {0xFF, 0xAA, 0x03, 0x07, 0x00, 0x00, 0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
		buf[7] = (BYTE)nVal;
		return m_ProcessCardComIO.SendData( buf, sizeof(buf)/sizeof(buf[0]));
	}
	//�Զ����濪
	BOOL GainOpen()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0xA7, 0x00, 0x00};
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	//�Զ������
	BOOL GainClose()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x82, 0x00, 0xA7, 0x00, 0x01};
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////���ذ�Ӧ��
	//Ӧ��
	BOOL Recv()
	{
		BYTE bBuf[ 4 ] = {0x03, 0x82, 0x00, 0x5F};
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////��ȡ�ھ���Ϣ
	BOOL GetInfo()
	{
		BYTE bBuf[ 6 ] = {0x05, 0x83, 0x00, 0x55, 0x00, 0xF0};
		return m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}

	////////////////////////////////////////////////////////////////////////////////////////////////���ð�ƽ��
	BOOL WhiteBalance()
	{
		//BYTE bBuf[ 7 ] = {0x06, 0x83, 0x00, 0x24, 0x01, 0x00, 0x08};
		BYTE cBuf[ 15 ] = {0xFF, 0xAA, 0x03, 0x0A, 0x00, 0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
		//AfxMessageBox("updatewhite");
		BOOL ok=m_ProcessCardComIO.SendData( cBuf, sizeof(cBuf)/sizeof(cBuf[0]));
		//BOOL ok2=m_VideoComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
		return ok;//&ok2;
	}

	////////////////////////////////////////////////////////////////////////
	BOOL Gain1()
	{
		BYTE bBuf[ 15 ] = {0xFF, 0xAA, 0x03, 0x07, 0x00, 0x00, 0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
		return m_ProcessCardComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	////////////////////////////////////////////////////////////////////////
	BOOL Gain5()
	{
		BYTE bBuf[ 15 ] = {0xFF, 0xAA, 0x03, 0x07, 0x00, 0x00, 0x00,0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
		return m_ProcessCardComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	BOOL Gain15()
	{
		BYTE bBuf[ 15 ] = {0xFF, 0xAA, 0x03, 0x07, 0x00, 0x00, 0x00,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
		return m_ProcessCardComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}

	BOOL MenuStart()
	{
		BYTE bBuf[ 15 ] = {0xFF, 0xAA, 0x03, 0x10, 0x00, 0x01, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
		return m_ProcessCardComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	BOOL MenuStop()
	{
		BYTE bBuf[ 15 ] = {0xFF, 0xAA, 0x03, 0x10, 0x00, 0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
		return m_ProcessCardComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	BOOL MenuUp()
	{
		BYTE bBuf[ 15 ] = {0xFF, 0xAA, 0x03, 0x11, 0x00, 0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
		return m_ProcessCardComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	BOOL MenuDown()
	{
		BYTE bBuf[ 15 ] = {0xFF, 0xAA, 0x03, 0x12, 0x00, 0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
		return m_ProcessCardComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	BOOL MenuLeft()
	{
		BYTE bBuf[ 15 ] = {0xFF, 0xAA, 0x03, 0x13, 0x00, 0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
		return m_ProcessCardComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	BOOL MenuRight()
	{
		BYTE bBuf[ 15 ] = {0xFF, 0xAA, 0x03, 0x14, 0x00, 0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
		return m_ProcessCardComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}
	BOOL MenuEnter()
	{
		BYTE bBuf[ 15 ] = {0xFF, 0xAA, 0x03, 0x15, 0x00, 0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
		return m_ProcessCardComIO.SendData( bBuf, sizeof(bBuf)/sizeof(bBuf[0]));
	}

	//�����ʾ����ָ��
	void GetShowDlgPointer( CWnd *pShowDlg );

	//���ڶ���
	CVideoComIO m_VideoComIO;
	CLightComIO m_LightComIO;
	CProcessCard m_ProcessCardComIO;
	
};


extern CPLC *g_pPLC;


