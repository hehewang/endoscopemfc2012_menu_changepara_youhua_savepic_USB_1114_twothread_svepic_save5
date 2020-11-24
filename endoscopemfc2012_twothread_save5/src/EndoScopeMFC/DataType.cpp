#include "pch.h"
#include "DataType.h"

//unsigned char NOWENTER[ 14 ] = {0x0D, 0x82, 0x00, 0x31, 0xD5, 0xFD, 0xD4, 0xDA, 0xC2, 0xBC, 0xC8, 0xEB, 0xFF, 0xFF};	
ZOOMSTRUCT picZoom = {0, 0, 1280, 720, 150};

HANDLE g_hPic2VideoThread;
HANDLE g_hSaveVideoThread;
HANDLE g_hSaveDataThread;

int g_FPS = 0;//����ͳ��֡��
int g_nSharpness = 0;			//������
int g_nBrightness = 0;			//����������
int g_nContrast = 0;			//�Աȶ�
int g_nSaturation = 5;			//���Ͷ�
int g_nExposure = 0;			//�ع�
int g_nGain = 0;				//����
int g_nWhitebalance=0;          //��ƽ��
int g_nLBrightness = 5;			//���Դ����
int g_nRed = 0;					//R����
int g_nBlue = 0;				//B����
int g_nMetering = 0;			//���ģʽ 0:ƽ�� 1:��ֵ
int g_nThresh = 255;//��ֵ
int g_nThreshNew = 255;//wm_20200919��ֵ
int g_nChangePixel = 3; //ѡ������ͨ������
int g_nChange255 = 0; //��ֵ255
int g_nShowShape = 0;			//��ʾ 0:���� 1:Բ��
int g_nPeek = 0;				//����ֵ
int g_ncout=0;//LJ731
int g_nAvg = 0;					//����ֵ
int g_nNBI = 4;		 	        //NBI 0;1;2;3�ĸ���λ 4�ر�NBI
int g_nVCOM = 0;				//��Ƶ����
int g_nLCOM = 0;				//���Դ����
int g_nCCOM=2;					//ͼ����崮��
int g_nPort = 8887;				//port
double g_lamdar=1.0 ;
double g_lamdab=1.0;
double g_lamdag=1.0;
double g_fGainR = 0;			//��ƽ��Rֵ
double g_fGainB = 0;			//��ƽ��Bֵ
int g_iMenu = 0;
int g_thred;
BOOL g_bFICE = FALSE;			//FICE
BOOL g_bExposure = FALSE;		//�Զ��ع�
BOOL g_bGain = FALSE;			//�Զ�����
BOOL g_bWhiteBalance = FALSE;	//�Զ���ƽ��

BOOL g_bIsLightOpen = FALSE;	//���Դ����
BOOL g_nOneSave = FALSE;		//����һ��ͼƬ
BOOL g_bIsUpan = FALSE;			//u�̲�����

BOOL g_bIsAutoLightOpen = TRUE;		//�Զ��������Դ
BOOL g_bOneSharpen = FALSE;		//����λ������һ����
BOOL g_bOneR = FALSE;			//����λ������һ��R����
BOOL g_bOneB = FALSE;			//����λ������һ��B����
BOOL g_bStop = FALSE;			//�������ֹͣ��Ƶ
BOOL g_bVideo = FALSE;			//¼��

BOOL g_bDeleteTemp = FALSE;		//ɾ���ļ�
BOOL g_bInputInfo = FALSE;		//������Ϣ
BOOL g_bConnect = FALSE;		//����socket

ULONG g_uTmpPic = 0;			//��ʱͼƬ��

CString g_decDriver = _T( "" );			//u���̷�
//20180111
CString g_strSaveDir = _T("DATA\\");//ͼƬ��Ƶ����·��
CString g_strTmpDir = _T("D:\\Temp\\");	//������ʱͼƬ·��
CString g_ConfigPath = _T( "" );		//�����ļ�·��
CString g_strIP = _T("192.168.1.145");	//ip
CString g_strName = _T( "" );	//��������
CString g_strID =_T( "" );		//����ID
CString g_strPatientInfo=_T("");

CString strAvg = _T("");		//���Ժ�ɾ��
CString strPeek = _T("");		//���Ժ�ɾ��

queue<BYTE *> g_Video_list;	//���֡����

map<unsigned int, double> g_Map_Sharpness;//�񻯶�Ӧ��ϵ
queue<string> g_Operate_list;			 //������¼�б�

CWnd *g_pShowDlg = NULL;		//��������ָ��

bool ReadConfig(void)
{
	CString strValue = _T(""),strValue1 = _T("");
	g_ConfigPath = ReturnPath() + _T("\\config.ini");

	GetPrivateProfileString(_T("PARAMETER"), _T("PATH"), _T("D:\\�ڿ�������\\"), g_strSaveDir.GetBuffer(512), 512, g_ConfigPath);
	g_strSaveDir.Trim();
	if (g_strSaveDir.Right(1) != "\\")
		g_strSaveDir.Append(_T("\\"));
	//g_nSharpness = GetPrivateProfileInt(_T("PARAMETER"), _T("SHARPNESS"), 1, g_ConfigPath);
	g_nBrightness = GetPrivateProfileInt(_T("PARAMETER"), _T("BRIGHTNESS"), 1, g_ConfigPath);
	g_nContrast = GetPrivateProfileInt(_T("PARAMETER"), _T("CONTRAST"), 1, g_ConfigPath);
	g_nSaturation = GetPrivateProfileInt(_T("PARAMETER"), _T("SATURATION"), 1, g_ConfigPath);
	g_nExposure = GetPrivateProfileInt(_T("PARAMETER"), _T("EXPOSURE"), 1, g_ConfigPath);
	g_nGain = GetPrivateProfileInt(_T("PARAMETER"), _T("GAIN"), 1, g_ConfigPath);
	g_nMetering = GetPrivateProfileInt(_T("PARAMETER"), _T("ADJBRIGHT"), 1, g_ConfigPath);
	g_bWhiteBalance = GetPrivateProfileInt(_T("PARAMETER"), _T("WHITEBALANCE"), 1, g_ConfigPath);
	g_nWhitebalance = GetPrivateProfileInt(_T("PARAMETER"), _T("WHITEBALANCEVAL"), 1, g_ConfigPath);
	g_nBlue = GetPrivateProfileInt(_T("PARAMETER"), _T("HUE_B"), 1, g_ConfigPath);
	g_nRed = GetPrivateProfileInt(_T("PARAMETER"), _T("HUE_R"), 1, g_ConfigPath);
	//g_bIsAutoLightOpen = GetPrivateProfileInt(_T("PARAMETER"), _T("AUTOLIGHT"), 1, g_ConfigPath);
	g_nShowShape = GetPrivateProfileInt(_T("PARAMETER"), _T("CONTUOR"), 0, g_ConfigPath); 
	g_bExposure = GetPrivateProfileInt(_T("PARAMETER"), _T("AUTOEXPOSURE"), 0, g_ConfigPath);
	g_thred=GetPrivateProfileInt(_T("PARAMETER"), _T("THRETH"), 0, g_ConfigPath);
	g_fGainR = GetPrivateProfileInt(_T("PARAMETER"), _T("GAIN_R"), 0, g_ConfigPath);
	g_fGainB = GetPrivateProfileInt(_T("PARAMETER"), _T("GAIN_B"), 0, g_ConfigPath);
	g_iMenu = GetPrivateProfileInt(_T("PARAMETER"), _T("MENU"), 3, g_ConfigPath);
	g_lamdar=GetPrivateProfileInt(_T("PARAMETER"), _T("LAMDAR"), 0, g_ConfigPath);
	g_lamdag=GetPrivateProfileInt(_T("PARAMETER"), _T("LAMDAG"), 0, g_ConfigPath);
	g_lamdab=GetPrivateProfileInt(_T("PARAMETER"), _T("LAMDAB"), 0, g_ConfigPath);
	g_nChangePixel = GetPrivateProfileInt(_T("PARAMETER"), _T("CHANGEPIXEL"), 3, g_ConfigPath);
	g_nThresh= GetPrivateProfileInt(_T("PARAMETER"), _T("THRETH2"), 255, g_ConfigPath);
	g_nChange255 = GetPrivateProfileInt(_T("PARAMETER"), _T("CHANGE255"), 0, g_ConfigPath);
	g_nThreshNew= GetPrivateProfileInt(_T("PARAMETER"), _T("THRETHNEW"), 255, g_ConfigPath);

	g_nVCOM = GetPrivateProfileInt(_T("COM"), _T("VCOMNUM"), 0, g_ConfigPath);
	g_nLCOM = GetPrivateProfileInt(_T("COM"), _T("LCOMNUM"), 0, g_ConfigPath);
	g_nCCOM=GetPrivateProfileInt(_T("COM"), _T("CCOMNUM"), 2, g_ConfigPath);

	g_bConnect = GetPrivateProfileInt(_T("SOCKET"), _T("ISCONNECT"), 0, g_ConfigPath);
	GetPrivateProfileString(_T("SOCKET"), _T("SERVERIP"), _T("192.168.1.248"), g_strIP.GetBuffer(32), 32, g_ConfigPath);
	g_nPort = GetPrivateProfileInt(_T("SOCKET"), _T("SERVERPORT"), 8887, g_ConfigPath);

	return TRUE;  // return TRUE unless you set the focus to a control
}

void SetConfig(CString keyname, double para)//д�����ļ�
{
	CString temp;
	temp.Format(_T("%lf"), para);
	WritePrivateProfileString(_T("PARAMETER"), keyname, temp, g_ConfigPath);

 	CString cstrTmp;
 	cstrTmp.Format( _T("insert into RecData (����, ����ֵ) Values('%s', '%lf')"), keyname, para);
	//USES_CONVERSION; 
 	string sql=(CT2A)cstrTmp.GetString(); 
	g_Operate_list.push( sql );

// 	bool ret = SQLiteHelper::GetInstance().InsertData(sql);  
// 	if (!ret)  
// 	{  
// 		string strTmp = SQLiteHelper::GetInstance().GetLastError();  
// 		g_Operate_list.pop();
// 		AfxMessageBox( _T("SaveError!") );
// 		return;  
// 	} 
}

CString ReturnPath()
{
	CString sPath;
	GetModuleFileName(NULL, sPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
	sPath.ReleaseBuffer();

	int nPos;
	nPos = sPath.ReverseFind('\\');
	sPath = sPath.Left(nPos);
	return sPath;
}