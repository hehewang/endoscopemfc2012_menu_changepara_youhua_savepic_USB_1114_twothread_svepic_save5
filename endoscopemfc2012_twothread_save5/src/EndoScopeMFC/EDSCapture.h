#pragma once

#include <iostream>

#include "afxstr.h"
#include <afxwin.h>
#include<vector>
#include "CEDSGrabberCB.h"
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x) if(NULL!=x){x->Release();x=NULL;}
#endif



//extern CCritSec g_dVideoLock;//¼�񻺴������
// CEDSGrabberCB����������Ҫ���ؼ������������ǻص�����


// CEDSCapture
class CEDSCapture : public CWnd
{
	DECLARE_DYNAMIC(CEDSCapture)
//friend class CEDSGrabberCB;
public:
	//void GrabOneFrame(BOOL bGrab);
	HRESULT Init(int iDeviceID,HWND hWnd);	// ������һЩDW��Ƶ��ʼ������
	void Pause();			// ��ͣ��Ƶ��׽
	void Run();		// ��Ƶ��׽
	void Stop();
	void GrabImage( CString );// ��׽��֡��Ƶͼ��
	void VideoAdjust( int ntype);// ��Ƶ��ǿ����
	void DeNoise();	// ��Ƶ����
	void Sharped();	// ��Ƶ��
	//void GetScale(int nw);	// ������Ƶ�봰�ڳߴ����
	//int EnumDevices(HWND hList);
	void StartWriteVideo();
	void StopWriteVideo();
	void StartWritePic();
	void StopWritePic();
	BYTE* GetFrame();
	BYTE* GetPicture();
	void SetupLamdaRGB();
	void SetZoom(double flag);
	bool GetStateWhiteBalance();
	CEDSCapture();
	virtual ~CEDSCapture();


public:
	float m_fscale_x,m_fscale_y;	// ��Ƶ�봰�ڳߴ����
	std::vector<IBaseFilter *> m_vecDevices;
	BYTE* m_pBuffer;//֡ ����
	int m_nWidth, m_nHeight;//��Ƶ���
private:
	// ö����Ƶ����״̬
	enum PLAYSTATE {
		Stopped, 
		Paused, 
		Running, 
		Init_Ready
	};
	enum PLAYSTATE m_psCurrent;
	HWND m_hApp;
	DWORD m_dwGraphRegister;
	BOOL m_bOneShot;
	CEDSGrabberCB g_CB;	// �˶��������Ƶ�ص�����
	IVideoWindow  *m_pVW;
	IMediaControl *m_pMC;
	IMediaEventEx *m_pME;
	IGraphBuilder *m_pGraph;
	ICaptureGraphBuilder2 *m_pCapture;
	CComPtr <ISampleGrabber> m_pGrabber;
protected:
	HRESULT GetInterfaces(void);		// ��������ȡDW�ӿ�
	HRESULT FindCaptureDevice(IBaseFilter ** ppSrcFilter);	// Ѱ�Ҳ�׽�豸
	HRESULT SetupVideoWindow(void);		// ������Ƶ����
	HRESULT ChangePreviewState(int nShow);
	HRESULT HandleGraphEvent(void);

	void Msg(TCHAR *szFormat, ...);
	void CloseInterfaces(void);			// �رսӿ�
	void ResizeVideoWindow(void);		// ������Ƶ���ڴ�С
	void FreeMediaType(AM_MEDIA_TYPE& mt);	// �ͷ�sample����

	DECLARE_MESSAGE_MAP()
};




