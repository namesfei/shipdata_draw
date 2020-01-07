
// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "test2.h"

#include "MainFrm.h"
#include "UpView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
	m_bSplitterCreated = false;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	//if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
	//	!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	//{
	//	TRACE0("δ�ܴ���������\n");
	//	return -1;      // δ�ܴ���
	//}

	//if (!m_wndStatusBar.Create(this))
	//{
	//	TRACE0("δ�ܴ���״̬��\n");
	//	return -1;      // δ�ܴ���
	//}
	//m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	//// TODO: �������Ҫ��ͣ������������ɾ��������
	//m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	//EnableDocking(CBRS_ALIGN_ANY);
	//DockControlBar(&m_wndToolBar);

	//ȥ����������������ʽ
	SetWindowLong(this->m_hWnd, GWL_STYLE, 0);
	//ȥ���߿�������ʽ
	SetWindowLong(this->m_hWnd, GWL_EXSTYLE, 0);
	//ȡ���˵���
	this->SetMenu(NULL);
	//ȥ���߿���������ʽ
	//long Style;
	SetWindowLong(this->m_hWnd, GWL_EXSTYLE, 0);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return TRUE;
}

// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame ��Ϣ�������



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: �ڴ����ר�ô����/����û���
	//������̬����
	//m_splitter.CreateStatic(this, 2, 1);//����һ�в��										//������ͼ
	//m_splitter.CreateView(0, 0, RUNTIME_CLASS(CUpView), CSize(500, 200), pContext);
	//m_splitter.CreateView(0, 0, RUNTIME_CLASS(CDownView), CSize(500, 300), pContext);

	//return true;
	CRect rc;

	// ��ȡ��ܴ��ڿͻ�����CRect���� 
	GetClientRect(&rc);

	// ������̬�ָ�ڣ�һ������ 
	if (!m_splitter.CreateStatic(this, 2, 1))
		return FALSE;

	// �����ϱߴ����е���ͼ 
	if (!m_splitter.CreateView(0, 0, RUNTIME_CLASS(CUpView), CSize(rc.Width(), rc.Height() * 3 / 5), pContext))

		return FALSE;

	// �����±ߴ����е���ͼ
	if (!m_splitter.CreateView(1, 0, RUNTIME_CLASS(CDownView), CSize(rc.Width(), rc.Height() * 2 / 5), pContext))

		return FALSE;
	m_bSplitterCreated = true;
	//return CFrameWnd::OnCreateClient(lpcs, pContext);
}


void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CFrameWnd::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	CRect rc;
	GetClientRect(&rc);
	if (m_bSplitterCreated) {
		m_splitter.SetRowInfo(0, rc.Height() *3 / 5, 10);
		m_splitter.SetRowInfo(1, rc.Height() * 2 / 5, 10);
		m_splitter.RecalcLayout();
	}

}
