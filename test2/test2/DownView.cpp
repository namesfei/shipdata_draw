// DownView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "test2.h"
#include "DownView.h"


// CDownView

IMPLEMENT_DYNCREATE(CDownView, CFormView)

CDownView::CDownView()
	: CFormView(IDD_DOWNVIEW)
{

}

CDownView::~CDownView()
{
}

void CDownView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDownView, CFormView)
END_MESSAGE_MAP()


// CDownView ���

#ifdef _DEBUG
void CDownView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDownView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDownView ��Ϣ�������
