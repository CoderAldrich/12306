#pragma once

#include "12306Client_MFC.h"

#define UM_LOGIN_SUCCESS (WM_USER+1)

// CLoginDlg �Ի���
class CMainFrame;
class CLoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLoginDlg)

public:
	CLoginDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLoginDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonLogin();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	BOOL GetRandCode();
	

private:
	CUrlWrapper* m_pCurlObj;
	CMainFrame* m_pMainFrm;
public:
	afx_msg void OnStnClickedStaticRandcode();
	virtual BOOL Create(UINT nIDTemplate, CWnd* pParentWnd = NULL);
	virtual BOOL Create(LPCTSTR lpszTemplateName,CWnd* pParentWnd = NULL);

};
