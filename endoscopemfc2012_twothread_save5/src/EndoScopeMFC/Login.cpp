// Login.cpp : ʵ���ļ�
//

#include "pch.h"
#include "EndoScopeMFC.h"
#include "Login.h"
#include "afxdialogex.h"
#include "CSetPSW.h"


// Login �Ի���

IMPLEMENT_DYNAMIC(Login, CDialogEx)

Login::Login(CWnd* pParent /*=NULL*/)
	: CDialogEx(Login::IDD, pParent)
{
	CString sPath;
	GetModuleFileName(NULL, sPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
	sPath.ReleaseBuffer();

	int nPos;
	nPos = sPath.ReverseFind('\\');
	sPath = sPath.Left(nPos);

	CString ConfigPath = sPath + _T("\\config.ini");

	GetPrivateProfileString(_T("LOGIN"),_T("USERNAME"),"",m_susername,sizeof(m_susername),ConfigPath);
	GetPrivateProfileString(_T("LOGIN"),_T("PASSWORD"),"",m_spassword,sizeof(m_spassword),ConfigPath);
}

Login::~Login()
{
}

void Login::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LOGIN_USERNAME, m_username);
	DDX_Control(pDX, IDC_LOGIN_PASSWORD, m_password);
}


BEGIN_MESSAGE_MAP(Login, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_SetPSW, &Login::OnBnClickedBtnSetpsw)
	ON_BN_CLICKED(IDOK, &Login::OnBnClickedOk)
END_MESSAGE_MAP()


// Login ��Ϣ�������


void Login::OnBnClickedBtnSetpsw()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CSetPSW m_DlgSetPSW;
	if (m_DlgSetPSW.DoModal() == IDOK)
	{
		::MessageBox(NULL, "�����޸ĳɹ�", TEXT("��ܰ��ʾ"), MB_OK | MB_TASKMODAL | MB_SETFOREGROUND);
	}
}


void Login::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString sPath;
	GetModuleFileName(NULL, sPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
	sPath.ReleaseBuffer();

	int nPos;
	nPos = sPath.ReverseFind('\\');
	sPath = sPath.Left(nPos);

	CString ConfigPath = sPath + _T("\\config.ini");

	GetPrivateProfileString(_T("LOGIN"), _T("USERNAME"), "", m_susername, sizeof(m_susername), ConfigPath);
	GetPrivateProfileString(_T("LOGIN"), _T("PASSWORD"), "", m_spassword, sizeof(m_spassword), ConfigPath);

	UpdateData(TRUE);
	CString usr,pss;
	m_username.GetWindowTextA(usr);
	m_password.GetWindowTextA(pss);
	m_showpassword = pss;
	m_showname = usr;
	if ((usr==m_susername)&&(pss==m_spassword))
	{
		CDialogEx::OnOK();
	}
	else
	{
		::MessageBox( NULL, "�û������������", TEXT("��¼��ʾ"), MB_OK | MB_TASKMODAL | MB_SETFOREGROUND );
		return;
	}
	CDialogEx::OnOK();
}


BOOL Login::OnInitDialog()
{
	CDialog::OnInitDialog();
	CString sPSW(m_spassword);
	if ("123" == sPSW)
	{
		m_MSGInfo.ShowWindow(SW_SHOW);
	}
	else
	{
		m_MSGInfo.ShowWindow(SW_HIDE);
	}
	return TRUE;
}
