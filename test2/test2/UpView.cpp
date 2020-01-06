// UpView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "test2.h"
#include "UpView.h"


// CUpView

IMPLEMENT_DYNCREATE(CUpView, CFormView)

CUpView::CUpView()
	: CFormView(IDD_UPVIEW)
	//, m_chart(0)
{

}

CUpView::~CUpView()
{
}

void CUpView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TCHART1, m_chart);
}

BEGIN_MESSAGE_MAP(CUpView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CUpView::OnBnClickedButton1)
END_MESSAGE_MAP()


// CUpView ���

#ifdef _DEBUG
void CUpView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CUpView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CUpView ��Ϣ�������


void CUpView::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CSeries lineSeries = (CSeries)m_chart.Series(0);

	lineSeries.Clear();

	for (int i = 0; i < 5000; i++)
	{
		lineSeries.AddXY((double)i*0.01, sin(i*0.01) + 1, NULL, NULL);

	}

}
