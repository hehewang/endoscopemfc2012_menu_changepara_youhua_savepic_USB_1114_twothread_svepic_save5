#pragma once
#include <directshow/DShow.h>
#include <directshow/qedit.h>
#include <list>
#include <array>
#include<streams.h>
#include<opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include<opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include<opencv2/highgui/highgui_c.h>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/video.hpp>
#include <opencv2/core/types_c.h>

#pragma comment(lib, "opencv_core320.lib")
#pragma comment(lib, "opencv_highgui320.lib")
#pragma comment(lib, "opencv_imgcodecs320.lib")
#pragma comment(lib, "opencv_imgproc320.lib")
#pragma comment(lib, "opencv_video320.lib")
#pragma comment(lib, "opencv_videoio320.lib")
extern CEvent g_videoevent;
extern CEvent g_resizeevent;
extern CEvent g_picevent;
using namespace cv;
class CEDSGrabberCB : public ISampleGrabberCB
{
public:
	long lWidth;	// ͼ���
	long lHeight;	// ͼ���
	long m_nSize;	// ��ռ�ֽ���
	//int roi_w ;
	//int roi_h;
	//int roi_c ;
	//int roi_r ;
	//Mat m_dst;
	bool m_bwhiteok;//��ƽ���Ƿ�������
	//double m_dZoom;    //�Ŵ���
	//Mat m_src;//����
	BYTE* buf;
	//std::list<BYTE*> m_pTaskList;//�����������
	//std::list<BYTE*> m_pPicList;//����ͼƬ����
	//std::list<BYTE*> m_pShowList;//��ʾ����
	//bool m_bwritevideo;
	//bool m_bwritepicture;
	bool m_badjwhite;//�Ƿ������ƽ��
	//bool m_bshowvideo;//��ʾ��־
	//double*m_lamda;//��ƽ��ϵ��
	CEDSGrabberCB();
	~CEDSGrabberCB();
	STDMETHODIMP_(ULONG) AddRef();
	STDMETHODIMP_(ULONG) Release();
	STDMETHODIMP QueryInterface(REFIID riid, void ** ppv);	// ��ѯ�ӿ�
	STDMETHODIMP SampleCB(double SampleTime, IMediaSample * pSample);	// ����media Sampleָ��Ļص���δ��
	STDMETHODIMP BufferCB(double dblSampleTime, BYTE * pBuffer, long lBufferSize);	// ����Sample bufferָ��Ļص���ʹ��	
	//void AdjWhiteBalance(unsigned char* src, int width, int height, unsigned char** dst);
	//void CalWhilteLamda(BYTE * buf);
	//void IniWhilteLamda();
	void CropImage(BYTE* src,BYTE**dst);
	//bool StartShowVideoThread();

};