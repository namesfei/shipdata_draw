// UpView.cpp : 实现文件
//

#include "stdafx.h"
#include "test2.h"
#include "UpView.h"
#include "ShipStatusOffline.h"

#define MAX_SIZE 12001
// CUpView

IMPLEMENT_DYNCREATE(CUpView, CFormView)

CUpView::CUpView()
	: CFormView(IDD_UPVIEW)

	, m_bcreat(false)
	, m_plotst(0)
{

}

CUpView::~CUpView()
{
}

void CUpView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TCHART1, m_chart);
	DDX_Control(pDX, IDC_TCHART2, m_chart2);
	DDX_Control(pDX, IDC_TCHART3, m_chart3);
	DDX_Control(pDX, IDC_TCHART4, m_chart4);
	DDX_Control(pDX, IDC_TCHART5, m_chart5);
	DDX_Control(pDX, IDC_TCHART7, m_chart6);
}

BEGIN_MESSAGE_MAP(CUpView, CFormView)
	ON_WM_ERASEBKGND()

//	ON_WM_SIZE()
ON_WM_SIZE()
ON_WM_TIMER()
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





//void CUpView::OnDraw(CDC* /*pDC*/)
//{
//	// TODO: 在此添加专用代码和/或调用基类
//	
//}


//void CUpView::OnInitialUpdate()
//{
//	CFormView::OnInitialUpdate();
//
//	// TODO: 在此添加专用代码和/或调用基类
//	m_plot();
//
//}


BOOL CUpView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//设置brush为希望的背景颜色
	CBrush backBrush(RGB(208, 217, 216));

	//保存旧的brush
	CBrush* pOldBrush = pDC->SelectObject(&backBrush);
	CRect rect;
	pDC->GetClipBox(&rect);

	//画需要的区域
	pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY);
	pDC->SelectObject(pOldBrush);

	return TRUE;
	//return CFormView::OnEraseBkgnd(pDC);
}


//void CUpView::OnBnClickedButton1()
//{
//
//	// TODO: 在此添加专用代码和/或调用基类
//	m_plot();
//}


void CUpView::m_plot()
{
	//读取船舶数据
	CShipStatusOffline* pNewDofData = CShipStatusOffline::Instance();
	std::vector<double> t;
	std::vector<STATUSDATA3DOF> shipStatus;
	pNewDofData->getShipStatusBySeaLevelAndWind(3, 95, t, shipStatus);

	//改变大小
	//CRect rc;
	//GetClientRect(&rc);
	////m_chart.put_Width(rc.Width()/3);
	//m_chart.SetWindowPos(NULL, 50, 40, (rc.Width() - 200) / 3, (rc.Height() - 80) / 2, SWP_NOZORDER);
	//m_chart2.SetWindowPos(NULL, 50, 40 + (rc.Height() - 80) / 2, (rc.Width() - 200) / 3, (rc.Height() - 80) / 2, SWP_NOZORDER);
	//m_chart3.SetWindowPos(NULL, 100 + (rc.Width() - 200) / 3, 40, (rc.Width() - 200) / 3, (rc.Height() - 80) / 2, SWP_NOZORDER);
	//m_chart4.SetWindowPos(NULL, 100 + (rc.Width() - 200) / 3, 40 + (rc.Height() - 80) / 2, (rc.Width() - 200) / 3, (rc.Height() - 80) / 2, SWP_NOZORDER);
	//m_chart5.SetWindowPos(NULL, 150 + 2 * (rc.Width() - 200) / 3, 40, (rc.Width() - 200) / 3, (rc.Height() - 80) / 2, SWP_NOZORDER);
	//m_chart6.SetWindowPos(NULL, 150 + 2 * (rc.Width() - 200) / 3, 40 + (rc.Height() - 80) / 2, (rc.Width() - 200) / 3, (rc.Height() - 80) / 2, SWP_NOZORDER);

	CSeries lineSeries[6];
	lineSeries[0] = (CSeries)m_chart.Series(0);
	lineSeries[1] = (CSeries)m_chart2.Series(0);
	lineSeries[2] = (CSeries)m_chart3.Series(0);
	lineSeries[3] = (CSeries)m_chart4.Series(0);
	lineSeries[4] = (CSeries)m_chart5.Series(0);
	lineSeries[5] = (CSeries)m_chart6.Series(0);
	for (size_t i = 0; i < 6; i++)
	{
		lineSeries[i].Clear();
	}

	//给序列装载数据1
	//COleSafeArray XValues;
	//COleSafeArray YValues;
	//DWORD Xnum[] = { MAX_SIZE };
	//DWORD Ynum[] = { MAX_SIZE };
	//XValues.Create(VT_R8, 1, Xnum);
	//YValues.Create(VT_R8, 1, Ynum);
	//long index = 0;
	//for (int i = 0; i < MAX_SIZE; i++) {
	//	XValues.PutElement(&index, &t[i]);
	//	YValues.PutElement(&index, &shipStatus[i]);
	//	index++;
	//}
	//lineSeries[0].AddArray(MAX_SIZE, YValues, XValues);

	//给序列装载数据2
	for (int i = 0; i < 12001; i++)
	{
		lineSeries[0].AddXY(t[i], shipStatus[i].dRoll, NULL, NULL);
		lineSeries[1].AddXY(t[i], shipStatus[i].dRollSpd, NULL, NULL);
		lineSeries[2].AddXY(t[i], shipStatus[i].dPitch, NULL, NULL);
		lineSeries[3].AddXY(t[i], shipStatus[i].dPitchSpd, NULL, NULL);
		lineSeries[4].AddXY(t[i], shipStatus[i].dHeave, NULL, NULL);
		lineSeries[5].AddXY(t[i], shipStatus[i].dHeaveSpd, NULL, NULL);
	}
}

void CUpView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (m_bcreat) {
		CRect rc;
		GetClientRect(&rc);
		m_chart.SetWindowPos(NULL, 50, 40, (rc.Width() - 200) / 3, (rc.Height() - 80) / 2, SWP_NOZORDER);
		m_chart2.SetWindowPos(NULL, 50, 40 + (rc.Height() - 80) / 2, (rc.Width() - 200) / 3, (rc.Height() - 80) / 2, SWP_NOZORDER);
		m_chart3.SetWindowPos(NULL, 100 + (rc.Width() - 200) / 3, 40, (rc.Width() - 200) / 3, (rc.Height() - 80) / 2, SWP_NOZORDER);
		m_chart4.SetWindowPos(NULL, 100 + (rc.Width() - 200) / 3, 40 + (rc.Height() - 80) / 2, (rc.Width() - 200) / 3, (rc.Height() - 80) / 2, SWP_NOZORDER);
		m_chart5.SetWindowPos(NULL, 150 + 2 * (rc.Width() - 200) / 3, 40, (rc.Width() - 200) / 3, (rc.Height() - 80) / 2, SWP_NOZORDER);
		m_chart6.SetWindowPos(NULL, 150 + 2 * (rc.Width() - 200) / 3, 40 + (rc.Height() - 80) / 2, (rc.Width() - 200) / 3, (rc.Height() - 80) / 2, SWP_NOZORDER);

	}
}


void CUpView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	CShipStatusOffline* pNewDofData = CShipStatusOffline::Instance();
	//std::vector<double> t;
	//std::vector<STATUSDATA3DOF> shipStatus;
	pNewDofData->getShipStatusBySeaLevelAndWind(3, 95, t, shipStatus);
	//m_plot();
	m_bcreat = true;
	SetTimer(1, 100, NULL);
}


void CUpView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//读取船舶数据
	CSeries lineSeries[6];
	lineSeries[0] = (CSeries)m_chart.Series(0);
	lineSeries[1] = (CSeries)m_chart2.Series(0);
	lineSeries[2] = (CSeries)m_chart3.Series(0);
	lineSeries[3] = (CSeries)m_chart4.Series(0);
	lineSeries[4] = (CSeries)m_chart5.Series(0);
	lineSeries[5] = (CSeries)m_chart6.Series(0);
	for (size_t i = 0; i < 6; i++)
	{
		lineSeries[i].Clear();
	}

	//给序列装载数据2
	for (int i = 0; i < 500; i++)
	{
		lineSeries[0].AddXY(t[i + m_plotst], shipStatus[i + m_plotst].dRoll, NULL, NULL);
		lineSeries[1].AddXY(t[i + m_plotst], shipStatus[i + m_plotst].dRollSpd, NULL, NULL);
		lineSeries[2].AddXY(t[i + m_plotst], shipStatus[i + m_plotst].dPitch, NULL, NULL);
		lineSeries[3].AddXY(t[i + m_plotst], shipStatus[i + m_plotst].dPitchSpd, NULL, NULL);
		lineSeries[4].AddXY(t[i + m_plotst], shipStatus[i + m_plotst].dHeave, NULL, NULL);
		lineSeries[5].AddXY(t[i + m_plotst], shipStatus[i + m_plotst].dHeaveSpd, NULL, NULL);
	}
	if (m_plotst + 500 == 12000)
		KillTimer(1);
	m_plotst++;
	CFormView::OnTimer(nIDEvent);
}
