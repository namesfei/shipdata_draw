// UpView.cpp : 实现文件
//

#include "stdafx.h"
#include "test2.h"
#include "UpView.h"
#include "ShipStatusOffline.h"

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


// CUpView 诊断

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


// CUpView 消息处理程序


void CUpView::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CSeries lineSeries[3];
	lineSeries[0] = (CSeries)m_chart.Series(0);
	lineSeries[1] = (CSeries)m_chart.Series(1);
	lineSeries[2] = (CSeries)m_chart.Series(2);
	CShipStatusOffline* pNewDofData = CShipStatusOffline::Instance();
	std::vector<double> t;
	std::vector<STATUSDATA3DOF> shipStatus;
	pNewDofData->getShipStatusBySeaLevelAndWind(3, 95, t, shipStatus);

	lineSeries[0].Clear();
	lineSeries[1].Clear();
	lineSeries[2].Clear();
	//lineSeries.AddXY(t, shipStatus, NULL, NULL);
	for (int i = 0; i < 12001; i++)
	{
		lineSeries[0].AddXY(t[i], shipStatus[i].dHeave, NULL, NULL);
		/*lineSeries[1].AddXY(t[i], shipStatus[i].dPitchSpd, NULL, NULL);
		lineSeries[2].AddXY(t[i], shipStatus[i].dHeaveAcc, NULL, NULL);*/
	}

}
