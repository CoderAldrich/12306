
// 12306Client_MFCView.h : CMy12306Client_MFCView ��Ľӿ�
//

#pragma once

class CMy12306Client_MFCView : public CView
{
protected: // �������л�����
	CMy12306Client_MFCView();
	DECLARE_DYNCREATE(CMy12306Client_MFCView)

// ����
public:
	CMy12306Client_MFCDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CMy12306Client_MFCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

};

#ifndef _DEBUG  // 12306Client_MFCView.cpp �еĵ��԰汾
inline CMy12306Client_MFCDoc* CMy12306Client_MFCView::GetDocument() const
   { return reinterpret_cast<CMy12306Client_MFCDoc*>(m_pDocument); }
#endif

