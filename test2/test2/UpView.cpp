// UpView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "test2.h"
#include "UpView.h"
#include "ShipStatusOffline.h"

#define MAX_SIZE 12001
// CUpView
std::vector<float> hangxiang;
std::vector<float> xx;
std::vector<float> yy;

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
	DDX_Control(pDX, IDC_TCHART1, m_chart1);
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


BOOL CUpView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//����brushΪϣ���ı�����ɫ
	CBrush backBrush(RGB(208, 217, 216));

	//����ɵ�brush
	CBrush* pOldBrush = pDC->SelectObject(&backBrush);
	CRect rect;
	pDC->GetClipBox(&rect);

	//����Ҫ������
	pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY);
	pDC->SelectObject(pOldBrush);

	return TRUE;
	//return CFormView::OnEraseBkgnd(pDC);
}

void CUpView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	//�����ؼ�����
	if (m_bcreat) {
		CRect rc;
		GetClientRect(&rc);
		m_chart1.SetWindowPos(NULL, 50, 40, (rc.Width() - 200) / 3, (rc.Height() - 80) / 2, SWP_NOZORDER);
		m_chart2.SetWindowPos(NULL, 50, 45 + (rc.Height() - 80) / 2, (rc.Width() - 200) / 3, (rc.Height() - 80) / 2, SWP_NOZORDER);
		m_chart3.SetWindowPos(NULL, 100 + (rc.Width() - 200) / 3, 40, (rc.Width() - 200) / 3, (rc.Height() - 80) / 2, SWP_NOZORDER);
		m_chart4.SetWindowPos(NULL, 100 + (rc.Width() - 200) / 3, 45 + (rc.Height() - 80) / 2, (rc.Width() - 200) / 3, (rc.Height() - 80) / 2, SWP_NOZORDER);
		m_chart5.SetWindowPos(NULL, 150 + 2 * (rc.Width() - 200) / 3, 40, (rc.Width() - 200) / 3, (rc.Height() - 80) / 2, SWP_NOZORDER);
		m_chart6.SetWindowPos(NULL, 150 + 2 * (rc.Width() - 200) / 3, 45 + (rc.Height() - 80) / 2, (rc.Width() - 200) / 3, (rc.Height() - 80) / 2, SWP_NOZORDER);

	}
}

void CUpView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	double temp=45,tempx=15000,tempy=20000;
	for (size_t i = 0; i < 1200; i++)
	{	
		if (i<=300)
		{
			tempx += 0.6 * sqrt(2);
			tempy += 0.6 * sqrt(2);

		}
		else if(i>300)
		{	
			temp += 0.2;
			if (temp >= 360)
			{
				temp -= 360;
			}
			tempx = 15376.523 + 171.887338*cos((135 - 0.2 * (i - 300)) * 3.1415926 / 180);
			tempy = 20133.44 + 171.887338*sin((135 - 0.2 * (i - 300)) * 3.1415926 / 180);
		}
		hangxiang.push_back(temp);
		xx.push_back(tempx);
		yy.push_back(tempy);
	}


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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//��ȡ��������
	CSeries lineSeries[6];
	lineSeries[0] = (CSeries)m_chart1.Series(0);
	lineSeries[1] = (CSeries)m_chart2.Series(0);
	lineSeries[2] = (CSeries)m_chart3.Series(0);
	lineSeries[3] = (CSeries)m_chart4.Series(0);
	lineSeries[4] = (CSeries)m_chart5.Series(0);
	lineSeries[5] = (CSeries)m_chart6.Series(0);


	for (size_t i = 0; i < 6; i++)
	{
		lineSeries[i].Clear();
	}

	//������װ������2
	int newst;
	float max2=0, max4=0, min2=30000, min4=30000;
	//��ȡ20������
	for (int i = 0; i < 200; i++)
	{
		newst = i + m_plotst;
		lineSeries[0].AddXY(t[newst], shipStatus[newst].dRoll, NULL, NULL);
		lineSeries[1].AddXY(t[newst], xx[newst], NULL, NULL);
		lineSeries[2].AddXY(t[newst], shipStatus[newst].dPitch, NULL, NULL);
		lineSeries[3].AddXY(t[newst], yy[newst], NULL, NULL);
		lineSeries[4].AddXY(t[newst], shipStatus[newst].dHeave, NULL, NULL);
		lineSeries[5].AddXY(t[newst], hangxiang[newst], NULL, NULL);	
		//��200���ڵ����ֵ����Сֵ
		//����2
		float temp2 = xx[newst];
		if (temp2>max2)
		{
			max2 = temp2;
		}
		if (temp2<min2)
		{
			min2 = temp2;
		}
		//����4
		float temp4 = yy[newst];
		if (temp4>max4)
		{
			max4 = temp4;
		}
		if (temp4<min4)
		{
			min4 = temp4;
		}
	}
	//��̬��������������
	CAxes axes2 = (CAxes)m_chart2.get_Axis();
	CAxis axisleft2 = axes2.get_Left();
	CAxes axes4 = (CAxes)m_chart4.get_Axis();
	CAxis axisleft4 = axes4.get_Left();
	if (max2-min2<30)
	{
		axisleft2.put_Increment(5);
	}
	else
	{
		axisleft2.put_Increment(20);
	}

	if (max4 - min4<30)
	{
		axisleft4.put_Increment(5);
	}
	else
	{
		axisleft4.put_Increment(20);
	}
	
	m_plotst++;//��ͼ������ʼ��
	if (m_plotst + 200 == 1200)
		KillTimer(1);
	
	CFormView::OnTimer(nIDEvent);
}
