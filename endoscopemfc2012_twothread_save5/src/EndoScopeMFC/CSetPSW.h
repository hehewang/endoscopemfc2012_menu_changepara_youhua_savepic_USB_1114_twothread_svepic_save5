#pragma once


// CSetPSW �Ի���

class CSetPSW : public CDialogEx
{
	DECLARE_DYNAMIC(CSetPSW)

public:
	CSetPSW(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSetPSW();

// �Ի�������
	enum { IDD = IDD_DLG_SetPSW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	bool noAnorD(const char* s);
};
