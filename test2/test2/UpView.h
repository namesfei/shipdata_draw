#pragma once
#include "tchart1.h"
#include "CSeries.h"


// CUpView ������ͼ

class CUpView : public CFormView
{
	DECLARE_DYNCREATE(CUpView)

protected:
	CUpView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	CTchart1 m_chart;
public:
	afx_msg void OnBnClickedButton1();
};


