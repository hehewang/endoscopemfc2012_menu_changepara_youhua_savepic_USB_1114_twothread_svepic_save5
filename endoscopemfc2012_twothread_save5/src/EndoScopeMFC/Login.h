#pragma once


// Login �Ի���

class Login : public CDialogEx
{
	DECLARE_DYNAMIC(Login)

public:
	Login(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Login();

// �Ի�������
	enum { IDD = IDD_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnSetpsw();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CEdit m_username;
	char m_susername[50];
	char m_spassword[50];
	CEdit m_password;
	CStatic m_MSGInfo;
	CString m_showpassword;//wm
	CString m_showname;//wm
};
