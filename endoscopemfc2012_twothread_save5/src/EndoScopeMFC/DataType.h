#pragma once

#include <time.h>
#include <sys/timeb.h>
#include <fstream>
#pragma warning(disable:4786)//ȥ��ʹ��mapʱ��һ�Ѹ澯
#include <map>
#include <queue>
#include <list>

#include <string>

using std::string;

using namespace std;

# define IMGWIDTH 1280//ԭ��Ƶ��
# define IMGHEIGHT 720//ԭ��Ƶ��
# define IMGSIZE IMGWIDTH*IMGHEIGHT*3//2764800 //������Ƶ�ߴ�720P 2764800   1080P 6220800

#define SAFE_DELETE( ptr ) if ((ptr) != NULL) { delete (ptr); (ptr) = NULL; }//deleteָ��
#define SAFE_DELETE_ARRAY( ptr ) if ((ptr) != NULL) { delete[] (ptr); (ptr) = NULL; }//delete����ָ��

//������
typedef enum {
	SHARPNESS0,
	SHARPNESS1,
	SHARPNESS2,
	SHARPNESS3,
	SHARPNESS4,
	SHARPNESS5,
	SHARPNESS6,
	SHARPNESS7,
	SHARPNESS8,
	SHARPNESS9,
	SHARPNESS10
} VIDEO_SHARPNESS;

//ͼ������
typedef enum {
	BRIGHTNESS0,
	BRIGHTNESS1,
	BRIGHTNESS2,
	BRIGHTNESS3,
	BRIGHTNESS4,
	BRIGHTNESS5,
	BRIGHTNESS6,
	BRIGHTNESS7,
	BRIGHTNESS8,
	BRIGHTNESS9,
	BRIGHTNESS10
} VIDEO_BRIGHTNESS;

typedef struct picZOOMSTRUCT
{
	int xSrc;
	int ySrc;
	int SrcWidth;
	int SrcHeight;
	int nCut;
	int nCutRect;
}ZOOMSTRUCT;

//�Աȶ�
typedef enum {
	Contrast0,
	Contrast1,
	Contrast2,
	Contrast3,
	Contrast4,
	Contrast5,
	Contrast6,
	Contrast7,
	Contrast8,
	Contrast9,
	Contrast10
} VIDEO_CONTRAST;

//���Ͷ�
typedef enum {
	SATURATION0,
	SATURATION1,
	SATURATION2,
	SATURATION3,
	SATURATION4,
	SATURATION5,
	SATURATION6,
	SATURATION7,
	SATURATION8,
	SATURATION9,
	SATURATION10
} VIDEO_SATURATION;

//�ع�
typedef enum {
	EXPOSURE0,
	EXPOSURE1,
	EXPOSURE2,
	EXPOSURE3,
	EXPOSURE4,
	EXPOSURE5,
	EXPOSURE6,
	EXPOSURE7,
	EXPOSURE8,
	EXPOSURE9,
	EXPOSURE10
} VIDEO_EXPOSURE;

//����
typedef enum {
	GAIN0,
	GAIN1,
	GAIN2,
	GAIN3,
	GAIN4,
	GAIN5,
	GAIN6,
	GAIN7,
	GAIN8,
	GAIN9,
	GAIN10
} VIDEO_GAIN;

//���Դ����
typedef enum {
	LGAIN0,
	LGAIN1,
	LGAIN2,
	LGAIN3,
	LGAIN4,
	LGAIN5,
	LGAIN6,
	LGAIN7,
	LGAIN8,
	LGAIN9,
	LGAIN10
} LIGHT_BRIGHTNESS;

//ͼ��Ŵ�
typedef enum {
	ZOOM1,
	ZOOM2,
	ZOOM3,
	ZOOM4,
} VIDEO_ZOOM;

//RED����
typedef enum {
	RED0,
	RED1,
	RED2,
	RED3,
	RED4,
	RED5,
	RED6,
	RED7,
	RED8,
	RED9,
	RED10,
} VIDEO_RED;

//BLUE����
typedef enum {
	BLUE0,
	BLUE1,
	BLUE2,
	BLUE3,
	BLUE4,
	BLUE5,
	BLUE6,
	BLUE7,
	BLUE8,
	BLUE9,
	BLUE10,
} VIDEO_BLUE;

//R��B��ʶ
enum {
	RED_SIGN,
	BLUE_SIGN
};
extern ZOOMSTRUCT picZoom;
extern HANDLE g_hPic2VideoThread;
extern HANDLE g_hSaveVideoThread;
extern HANDLE g_hSaveDataThread;
extern int g_FPS;//����ͳ��֡��
extern int g_thred;
extern int g_nSharpness;	//������
extern int g_nBrightness;	//ͼ������
extern int g_nContrast;		//�Աȶ�
extern int g_nSaturation;	//���Ͷ�
extern int g_nExposure;		//�ع�
extern int g_nGain;			//����
extern int g_nWhitebalance; //��ƽ��
extern int g_nLBrightness;	//���Դ����

extern int g_nRed;			//R����
extern int g_nBlue;			//B����
extern int g_nMetering;		//���ģʽ 0:ƽ�� 1:��ֵ
extern int g_nPic;			//�洢��Ƭ��
extern int g_nShowShape;	//��ʾ 0:���� 1:Բ��
extern int g_nPeek;			//����ֵ
extern int g_ncout;//LJ731
extern int g_nAvg;			//����ֵ
extern int g_nNBI;			//NBI
extern int g_nVCOM;			//��Ƶ����
extern int g_nLCOM;			//���Դ����
extern int g_nCCOM;         //ͼ����崮��
extern int g_nPort;			//port
extern double g_lamdar;   //R��ϵ��
extern double g_lamdab;
extern double g_lamdag;
extern double g_fGainR;		//��ƽ��Rֵ
extern double g_fGainB;		//��ƽ��Bֵ
extern int g_iMenu;			//�˵�

extern BOOL g_bFICE;		//FICE
extern BOOL g_bExposure;	//�Զ��ع�
extern BOOL g_bGain;		//�Զ�����
extern BOOL g_bWhiteBalance;//�Զ���ƽ��
extern BOOL g_bIsLightOpen;	//���Դ����
extern BOOL g_nOneSave;		//����һ��ͼƬ
extern BOOL g_bIsUpan;		//u�̲�����
extern BOOL g_bIsAutoLightOpen;		//�Զ��������Դ
extern BOOL g_bOneSharpen;	//����λ������һ����
extern BOOL g_bOneR;		//����λ������һ��R����
extern BOOL g_bOneB;		//����λ������һ��B����
extern BOOL	g_bStop;		//�������ֹͣ��Ƶ
extern BOOL g_bVideo;		//¼��
extern BOOL g_bDeleteTemp;	//ɾ���ļ�
extern BOOL g_bInputInfo;	//������Ϣ
extern BOOL g_bConnect;		//����socket

extern ULONG g_uTmpPic;		//��ʱͼƬ��

extern CString g_decDriver;	//u���̷�
extern CString g_strSaveDir;//ͼƬ��Ƶ����·��
extern CString g_strTmpDir;	//������ʱͼƬ·��
extern CString g_ConfigPath;//�����ļ�·��
extern CString g_strIP;		//ip
extern CString g_strName;	//��������
extern CString g_strID;		//����ID
extern CString g_strPatientInfo;

extern CString strAvg;		//���Ժ�ɾ��
extern CString strPeek;		//���Ժ�ɾ��

extern queue<BYTE *> g_Video_list;	//���֡����

extern map<unsigned int, double> g_Map_Sharpness;//�񻯶�Ӧ��ϵ
extern queue<string> g_Operate_list;			 //������¼�б�

extern CWnd *g_pShowDlg;						 //��������ָ��

class CComDataHandler
{
public:
	virtual void ProcessData( unsigned char* pBuf, int size) = 0;
};

class CRetryInfo  
{
public:
	short m_siFrame;
	short m_siRetryCount;
	CTime sendtime;
	BYTE sendbuf[64];
	int sendlength;
	bool operator == (const CRetryInfo &RetryInfo) const
	{
		if (this->m_siFrame == RetryInfo.m_siFrame)
			return true;
		else
			return false;
	}

protected:
private:
};

extern CString ReturnPath();

extern bool ReadConfig(void);

extern void SetConfig(CString keyname, double para);


