#pragma once



// CDownView ������ͼ

class CDownView : public CFormView
{
	DECLARE_DYNCREATE(CDownView)

protected:
	CDownView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CDownView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DOWNVIEW };
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
};


