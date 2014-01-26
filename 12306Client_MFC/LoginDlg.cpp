// LoginDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MainFrm.h"
#include "LoginDlg.h"
#include "afxdialogex.h"
#include <regex>
#include <json\json.h>
#include "Operate.h"

#define LOG(_l) m_pMainFrm->ShowLog(_l)
#define TIMER_RANDCODE 1
// CLoginDlg �Ի���

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLoginDlg::IDD, pParent)
{
	
}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CLoginDlg::OnBnClickedButtonLogin)
	ON_WM_TIMER()
	ON_STN_CLICKED(IDC_STATIC_RANDCODE, &CLoginDlg::OnStnClickedStaticRandcode)
END_MESSAGE_MAP()


// CLoginDlg ��Ϣ�������


void CLoginDlg::OnBnClickedButtonLogin()
{
	//::PostMessage(GetParent()->GetSafeHwnd(), UM_LOGIN_SUCCESS, 0, 0);return;
	// �����֤����ȷ��
	// "randCode=by7b&rand=sjrand";
	const char* url = "https://kyfw.12306.cn/otn/passcodeNew/checkRandCodeAnsyn";
	CString strCode;
	char post_fields[128] = {'\0'};
	strcat_s(post_fields, 128, "randCode=");
	GetDlgItemText(IDC_EDIT_RANDCODE, strCode);
	if(strCode.IsEmpty())
	{
		LOG(L"��������֤��!");
		return;
	}
	LOG(L"У����֤��...");
	size_t converted;
	::wcstombs_s(&converted, post_fields+strlen(post_fields),128-strlen(post_fields), strCode, strCode.GetLength()*sizeof(TCHAR));
	strcat_s(post_fields+strlen(post_fields), 128-strlen(post_fields), "&rand=sjrand");
	if(m_pCurlObj->doHttpsPost(url, post_fields))
	{
		size_t response_len = m_pCurlObj->getResponseLength();
		if(response_len)
		{
			char* response = new char[response_len];
			memset(response, '\0', response_len);
			m_pCurlObj->getResponseData(response, response_len);
			std::string strRes;
			strRes.append(response);
			delete[] response;
			size_t pos = strRes.rfind("data");
			if(std::string::npos == pos)
			{
				LOG(L"12306ò���ָ����ˣ�����ϵ����lniwn@126.com !");
				return;
			}
			pos = strRes.find("\"Y\"", pos);
			if(std::string::npos == pos)
			{
				LOG(L"��֤��������������룡");
				return;
			}
			
		}
		else
		{
			LOG(L"�޷��ӷ�������ȡ��Ӧ��Ϣ��");
			return;
		}
	}
	else
	{
		LOG(L"���������ύ����ʧ�ܣ������ԣ�");
		return;
	}
	LOG(L"У��ɹ���");

	// ��¼
	// loginUserDTO.user_name=test___12306&userDTO.password=test___12306_a&randCode=bxre
	CString strName, strPwd;
	GetDlgItemText(IDC_EDIT_USERNAME, strName);
	GetDlgItemText(IDC_EDIT_USERPWD, strPwd);
	if(strName.IsEmpty() || strPwd.IsEmpty())
	{
		LOG(L"�������û���������!");
		return;
	}
	
	LOG(L"�ύ��¼��Ϣ...");
	url = "https://kyfw.12306.cn/otn/login/loginAysnSuggest";
	memset(post_fields, '\0', 128);
	strcat_s(post_fields, 128, "loginUserDTO.user_name=");
	::wcstombs_s(&converted, post_fields+strlen(post_fields),128-strlen(post_fields), strName, strName.GetLength()*sizeof(TCHAR));
	strcat_s(post_fields+strlen(post_fields), 128-strlen(post_fields), "&userDTO.password=");
	::wcstombs_s(&converted, post_fields+strlen(post_fields),128-strlen(post_fields), strPwd, strPwd.GetLength()*sizeof(TCHAR));
	strcat_s(post_fields+strlen(post_fields), 128-strlen(post_fields), "&randCode=");
	::wcstombs_s(&converted, post_fields+strlen(post_fields),128-strlen(post_fields), strCode, strCode.GetLength()*sizeof(TCHAR));
	if(m_pCurlObj->doHttpsPost(url, post_fields))
	{
		size_t response_len = m_pCurlObj->getResponseLength();
		
		if(response_len)
		{
			char* const response = new char[response_len];
			do
			{
				Json::Reader JReader;
				Json::Value JObject;
				memset(response, '\0', response_len);
				m_pCurlObj->getResponseData(response, response_len);

				std::string strRes(response);
				size_t offset = strRes.find("\r\n\r\n");
				if(offset != std::string::npos)
				{
					offset = strRes.find("{", offset);
					if(offset != std::string::npos)
					{
						strRes.clear();
					}
					else
					{
						break;
					}

				}
				else
				{
					break;
				}
				if(!JReader.parse(response+offset, JObject, false))
				{
					break;
				}

				const Json::Value login_check = JObject["data"]["loginCheck"];
				if(login_check.isNull())
				{
					const Json::Value msg_arr = JObject["messages"];
					if(msg_arr.size()!=0)
					{
						strRes = msg_arr[(Json::UInt)0].asString();
						char msg_buf[128] = {'\0'};
						TCHAR wcs_buf[128] = {0};
						int wcs_len = ::MultiByteToWideChar(CP_UTF8, 0, strRes.c_str(), strRes.size(), NULL, 0);
						::MultiByteToWideChar(CP_UTF8, 0, strRes.c_str(), strRes.size(), wcs_buf, wcs_len);
						LOG(wcs_buf);
					}

				}
				else
				{
					if(0 == _strcmpi(login_check.asString().c_str(), "y"))
					{
						LOG(L"��¼�ɹ�!");
						::PostMessage(GetParent()->GetSafeHwnd(), UM_LOGIN_SUCCESS, 0, 0);
					}
				}
				delete[] response;
				return;
			}while(0);
			
			LOG(L"12306ò���ָ����ˣ�����ϵ����lniwn@126.com !");
			delete[] response;
		}
		else
		{
			LOG(L"�޷��ӷ�������ȡ��Ӧ��Ϣ��");
		}
	}
	else
	{
		LOG(L"���������ύ����ʧ�ܣ�");
	}
	LOG(L"��¼ʧ�ܣ�");
}


BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ASSERT(theApp.m_pCurlObj);
	m_pCurlObj = theApp.m_pCurlObj;

	ASSERT_VALID(m_pMainFrm);
	GetRandCode();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CLoginDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnTimer(nIDEvent);
}


BOOL CLoginDlg::GetRandCode()
{
	LOG(L"��ȡ��֤��...");
	char url[512] = {0};
	strcat_s(url, 512, "https://kyfw.12306.cn/otn/passcodeNew/getPassCodeNew.do?module=login&rand=sjrand&");
	char code[30] = {0};
	m_pCurlObj->getRandom(code, 30);
	strcat_s(url, 512 - strlen(url), code);
	if(m_pCurlObj->doHttpsGet(url))
	{
		size_t len = m_pCurlObj->getResponseLength();
		
		if(len)
		{
			byte* const data = new byte[len];
			memset(data, '\0', len);
			m_pCurlObj->getResponseData(data, len);
			byte* png = data;
			// ȥ��Response Header
			while(isascii(*png++));
			--png;
			IStream* pStream;
			HGLOBAL hGlobal = CreateStreamFromMemory(png, len, &pStream);
			CImage img;
			if(SUCCEEDED(img.Load(pStream)))
			{
				((CStatic*)GetDlgItem(IDC_STATIC_RANDCODE))->SetBitmap(img);
				LOG(L"��ȡ��֤��ɹ���");
				::GlobalFree(hGlobal);
				img.Detach();
				delete[] data;
				return TRUE;
			}
			::GlobalFree(hGlobal);
			delete[] data;
		}
	}
	LOG(L"��ȡ��֤��ʧ�ܣ�");
	return FALSE;
}


void CLoginDlg::OnStnClickedStaticRandcode()
{
	GetRandCode();
}

BOOL CLoginDlg::Create(UINT nIDTemplate, CWnd* pParentWnd)
{
	m_pMainFrm = DYNAMIC_DOWNCAST(CMainFrame,pParentWnd);
	ASSERT_VALID(m_pMainFrm);
	return CDialogEx::Create(nIDTemplate, pParentWnd);
}

BOOL CLoginDlg::Create(LPCTSTR lpszTemplateName,CWnd* pParentWnd)
{
	m_pMainFrm = DYNAMIC_DOWNCAST(CMainFrame,pParentWnd);
	ASSERT_VALID(m_pMainFrm);
	return CDialogEx::Create(lpszTemplateName, pParentWnd);
}