
// 12306Client_MFC.h : 12306Client_MFC Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������

#include "UrlWrapper.h"

// CMy12306Client_MFCApp:
// �йش����ʵ�֣������ 12306Client_MFC.cpp
//

class CMy12306Client_MFCApp : public CWinApp
{
public:
	CMy12306Client_MFCApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	CUrlWrapper* m_pCurlObj;
	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy12306Client_MFCApp theApp;
