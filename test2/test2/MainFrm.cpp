
// MainFrm.cpp : CMainFrame 类的实现
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
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
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
	//	TRACE0("未能创建工具栏\n");
	//	return -1;      // 未能创建
	//}

	//if (!m_wndStatusBar.Create(this))
	//{
	//	TRACE0("未能创建状态栏\n");
	//	return -1;      // 未能创建
	//}
	//m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	//// TODO: 如果不需要可停靠工具栏，则删除这三行
	//m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	//EnableDocking(CBRS_ALIGN_ANY);
	//DockControlBar(&m_wndToolBar);

	//去掉标题栏及其他样式
	SetWindowLong(this->m_hWnd, GWL_STYLE, 0);
	//去掉边框及其他样式
	SetWindowLong(this->m_hWnd, GWL_EXSTYLE, 0);
	//取消菜单栏
	this->SetMenu(NULL);
	//去掉边框风格及其他样式
	//long Style;
	SetWindowLong(this->m_hWnd, GWL_EXSTYLE, 0);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

// CMainFrame 诊断

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


// CMainFrame 消息处理程序



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类
	//创建静态窗口
	//m_splitter.CreateStatic(this, 2, 1);//两行一列拆分										//创建视图
	//m_splitter.CreateView(0, 0, RUNTIME_CLASS(CUpView), CSize(500, 200), pContext);
	//m_splitter.CreateView(0, 0, RUNTIME_CLASS(CDownView), CSize(500, 300), pContext);

	//return true;
	CRect rc;

	// 获取框架窗口客户区的CRect对象 
	GetClientRect(&rc);

	// 创建静态分割窗口，一行两列 
	if (!m_splitter.CreateStatic(this, 2, 1))
		return FALSE;

	// 创建上边窗格中的视图 
	if (!m_splitter.CreateView(0, 0, RUNTIME_CLASS(CUpView), CSize(rc.Width(), rc.Height() * 3 / 5), pContext))

		return FALSE;

	// 创建下边窗格中的视图
	if (!m_splitter.CreateView(1, 0, RUNTIME_CLASS(CDownView), CSize(rc.Width(), rc.Height() * 2 / 5), pContext))

		return FALSE;
	m_bSplitterCreated = true;
	//return CFrameWnd::OnCreateClient(lpcs, pContext);
}


void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CFrameWnd::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	CRect rc;
	GetClientRect(&rc);
	if (m_bSplitterCreated) {
		m_splitter.SetRowInfo(0, rc.Height() *3 / 5, 10);
		m_splitter.SetRowInfo(1, rc.Height() * 2 / 5, 10);
		m_splitter.RecalcLayout();
	}

}
