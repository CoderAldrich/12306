
// 12306Client_MFCView.cpp : CMy12306Client_MFCView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "12306Client_MFC.h"
#endif

#include "12306Client_MFCDoc.h"
#include "12306Client_MFCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy12306Client_MFCView

IMPLEMENT_DYNCREATE(CMy12306Client_MFCView, CView)

BEGIN_MESSAGE_MAP(CMy12306Client_MFCView, CView)
END_MESSAGE_MAP()

// CMy12306Client_MFCView ����/����

CMy12306Client_MFCView::CMy12306Client_MFCView()
{
	// TODO: �ڴ˴���ӹ������

}

CMy12306Client_MFCView::~CMy12306Client_MFCView()
{
}

BOOL CMy12306Client_MFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMy12306Client_MFCView ����

void CMy12306Client_MFCView::OnDraw(CDC* /*pDC*/)
{
	CMy12306Client_MFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CMy12306Client_MFCView ���

#ifdef _DEBUG
void CMy12306Client_MFCView::AssertValid() const
{
	CView::AssertValid();
}

void CMy12306Client_MFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy12306Client_MFCDoc* CMy12306Client_MFCView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy12306Client_MFCDoc)));
	return (CMy12306Client_MFCDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy12306Client_MFCView ��Ϣ�������


