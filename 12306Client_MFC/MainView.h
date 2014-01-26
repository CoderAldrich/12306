#pragma once
#include "resource.h"
#include <string>
#include "TBListCtrl.h"

typedef struct _TicketItem
{
	std::string station_train_code; // ����
	std::string start_station_name; // ʼ��վ
	std::string end_station_name;	// �յ�վ
	std::string from_station_name;	// ��ʼվ
	std::string to_station_name;	// ����վ
	std::string start_time;			// ��ʼʱ��
	std::string arrive_time;		// ����ʱ��
	std::string day_difference;		// ����
	std::string lishi;				// ����ʱ��
	bool canWebBuy;					// �Ƿ�������繺Ʊ
	std::string lishiValue;			// ����ʱ��(����)
	std::string yp_info;			// ��Ʊ��Ϣ
	std::string seat_feature;		// ��λ�ص�(�����õģ���)
	std::string yp_ex;				// ��Ʊ��չ��Ϣ
	std::string swz_num;			// ������
	std::string tz_num;				// �ص���
	std::string zy_num;				// һ���� zuo yi
	std::string ze_num;				// ������ zuo er
	std::string gr_num;				// �߼�����
	std::string rw_num;				// ����
	std::string yw_num;				// Ӳ��
	std::string rz_num;				// ����
	std::string yz_num;				// Ӳ��
	std::string wz_num;				// ����
	std::string qt_num;				// ����
	std::string buttonTextInfo;		// ��ť����
	std::string secretStr;			// ��Ʊ��ʶ��
}TICKETITEM, *PTICKETITEM;

// CMainView �Ի���
class CUrlWrapper;
class CMainView : public CDialogEx
{
	DECLARE_DYNAMIC(CMainView)

public:
	CMainView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMainView();
	BOOL GetCityCode(LPCTSTR lpszCity, CString& strCode);

// �Ի�������
	enum { IDD = IDD_DIALOG_MAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	void ShowTrainInfo(char* buffer, int len);
	void ClearItemData(int item = -1);
	BOOL GetRandCode();

private:
	CMap<CString, LPCTSTR, CString, LPCTSTR> m_mapCity;
	TCHAR* m_pCityBuffer;
	DWORD m_lCityBuffer;
	CUrlWrapper* m_pCurlObj;
	std::string m_strDate;

public:
	CTBListCtrl m_lctrlMain;
	afx_msg void OnBnClickedButtonQuery();

	// wParam: item
	// lParam: subItem
	afx_msg LRESULT OnBnClickedBook(WPARAM wParam, LPARAM lParam); 

	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
};
