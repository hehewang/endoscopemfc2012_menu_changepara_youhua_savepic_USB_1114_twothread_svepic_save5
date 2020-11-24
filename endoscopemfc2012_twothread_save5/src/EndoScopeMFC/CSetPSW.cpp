// CSetPSW.cpp : ʵ���ļ�
//

#include "pch.h"
#include "EndoScopeMFC.h"
#include "CSetPSW.h"
#include "afxdialogex.h"
#include <ctype.h>


// CSetPSW �Ի���

IMPLEMENT_DYNAMIC(CSetPSW, CDialogEx)

CSetPSW::CSetPSW(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetPSW::IDD, pParent)
{

}

CSetPSW::~CSetPSW()
{
}

void CSetPSW::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSetPSW, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSetPSW::OnBnClickedOk)
END_MESSAGE_MAP()


// CSetPSW ��Ϣ�������


void CSetPSW::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString sPath;
	GetModuleFileName(NULL, sPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
	sPath.ReleaseBuffer();

	int nPos;
	nPos = sPath.ReverseFind('\\');
	sPath = sPath.Left(nPos);

	CString ConfigPath = sPath + _T("\\config.ini");
	char cPSW[50];
	memset(cPSW, 0, 50 * sizeof(char));
	GetPrivateProfileString("LOGIN", "PASSWORD", "", cPSW, 50 * sizeof(char), ConfigPath);
	CString sOldPSW(cPSW);

	CString sOld,sNew,sNew2;
	GetDlgItemText(IDC_EDIT_OLDPSW, sOld);
	GetDlgItemText(IDC_EDIT_NEWPSW, sNew);
	GetDlgItemText(IDC_EDIT_NEWPSW2, sNew2);
	if ("" == sOld)
	{
		::MessageBox(NULL, "ԭ���벻��Ϊ�գ�", "��ܰ��ʾ", MB_OK | MB_TASKMODAL | MB_SETFOREGROUND);
		return;
	}
	if (sOldPSW != sOld)
	{
		::MessageBox(NULL, "ԭ�����������", "��ܰ��ʾ", MB_OK | MB_TASKMODAL | MB_SETFOREGROUND);
		return;
	}
	if ("" == sNew)
	{
		::MessageBox(NULL, "�����벻��Ϊ�գ�", "��ܰ��ʾ", MB_OK | MB_TASKMODAL | MB_SETFOREGROUND);
		return;
	}
	if (sOld == sNew)
	{
		::MessageBox(NULL, "�����벻�ܺ�ԭ������ͬ��", "��ܰ��ʾ", MB_OK | MB_TASKMODAL | MB_SETFOREGROUND);
		return;
	}
	//����Ƿ��������ַ�
	char* pNewPSW = sNew.GetBuffer(0);
	if (noAnorD(pNewPSW))
	{
		::MessageBox(NULL, "������ֻ�ܰ���Ӣ����ĸ�����֣���ǣ���", "��ܰ��ʾ", MB_OK | MB_TASKMODAL | MB_SETFOREGROUND);
		return;
	}

	if (sNew2 == sNew)
	{
		WritePrivateProfileString("LOGIN", "PASSWORD", sNew, ConfigPath);
	}
	else
	{
		::MessageBox(NULL, "�������������벻һ�£�", "��ܰ��ʾ", MB_OK | MB_TASKMODAL | MB_SETFOREGROUND);
		return;
	}
	CDialogEx::OnOK();
}
bool CSetPSW::noAnorD(const char* s)
{
	// TODO: �ڴ˴����ʵ�ִ���.
	int r;
	r = 0;
	while(1)
	{
		if (*s == 0) break;
		if (!(isalpha(*s) | isdigit(*s)))//ֻ�ܰ������Ӣ�Ĵ�д��Сд��ĸ���ǰ���������
			return true;
		s++;
	}
	return false;
}
