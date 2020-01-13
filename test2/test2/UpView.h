#pragma once
#include "tchart1.h"
#include <vector>
#include "ShipStatusOffline.h"
#include "CAxis.h"
#include "CAxes.h"
// CUpView 窗体视图

class CUpView : public CFormView
{
	DECLARE_DYNCREATE(CUpView)

protected:
	CUpView();           // 动态创建所使用的受保护的构造函数
	virtual ~CUpView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UPVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CTchart1 m_chart1;
public:
//	afx_msg void OnBnClickedButton1();
//	virtual void OnDraw(CDC* /*pDC*/);
//	virtual void OnInitialUpdate();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	CTchart1 m_chart2;
	CTchart1 m_chart3;
	CTchart1 m_chart4;
	CTchart1 m_chart5;
	CTchart1 m_chart6;
//	afx_msg void OnBnClickedButton1();
//	void m_plot();
//	afx_msg void OnSize(UINT nType, int cx, int cy);
//	virtual void OnDraw(CDC* /*pDC*/);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnInitialUpdate();
private:
	bool m_bcreat;
	std::vector<double> t;
	std::vector<STATUSDATA3DOF> shipStatus;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
private:
	int m_plotst;
};


