
// MutilThread2Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MutilThread2.h"
#include "MutilThread2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMutilThread2Dlg 对话框



CMutilThread2Dlg::CMutilThread2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MUTILTHREAD2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	sum = 0;
	myThread = NULL;
	isRunning = FALSE;
}

void CMutilThread2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMutilThread2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_START, &CMutilThread2Dlg::OnBnClickedBtnStart)
	ON_BN_CLICKED(IDC_BTN_SUSPEND, &CMutilThread2Dlg::OnBnClickedBtnSuspend)
	ON_BN_CLICKED(IDC_BTN_RESUME, &CMutilThread2Dlg::OnBnClickedBtnResume)
	ON_BN_CLICKED(IDC_BTN_SHOW, &CMutilThread2Dlg::OnBnClickedBtnShow)
	ON_BN_CLICKED(IDC_BTN_STOP, &CMutilThread2Dlg::OnBnClickedBtnStop)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CMutilThread2Dlg 消息处理程序

BOOL CMutilThread2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMutilThread2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMutilThread2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMutilThread2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

UINT CMutilThread2Dlg::ThreadFun(LPVOID lpParam)
{
	CMutilThread2Dlg* pDlg = (CMutilThread2Dlg*)lpParam;
	CString str;
	
	for (;;) {
		if (pDlg->isRunning == FALSE) {
			return 0;
		}
		pDlg->g_ctrticalSection.Lock();
		pDlg->sum += 1;
		pDlg->g_ctrticalSection.Unlock();
		str.Format(_T("%d"), pDlg->sum);
		::SetDlgItemText(AfxGetApp()->m_pMainWnd->m_hWnd, IDC_EDIT_SUM, str);
		Sleep(10);
	}
	
	return 0;
}


void CMutilThread2Dlg::OnBnClickedBtnStart()
{
	// TODO: 在此添加控件通知处理程序代码
	if (myThread != NULL) {
		delete myThread;
		myThread = NULL;
	}
	sum = 0;
	isRunning = TRUE;
	myThread = AfxBeginThread(
		ThreadFun,
		this,
		THREAD_PRIORITY_NORMAL,
		0,
		THREAD_SUSPEND_RESUME,
		0
	);
	if (!myThread) {
		MessageBox(_T("创建线程失败"));
	}
	else {
		myThread->m_bAutoDelete = FALSE;
		myThread->ResumeThread();
	}
}



void CMutilThread2Dlg::OnBnClickedBtnSuspend()
{
	// TODO: 在此添加控件通知处理程序代码
	if (myThread)
	    myThread->SuspendThread();
}


void CMutilThread2Dlg::OnBnClickedBtnResume()
{
	// TODO: 在此添加控件通知处理程序代码
	if (myThread)
	    myThread->ResumeThread();
}


void CMutilThread2Dlg::OnBnClickedBtnShow()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox(_T("Main thread msg"));
}


void CMutilThread2Dlg::OnBnClickedBtnStop()
{
	// TODO: 在此添加控件通知处理程序代码
	if (myThread) {
		isRunning = FALSE;
		//WaitForSingleObject(myThread, 5000);
		ThreadFun_WaitForObject(myThread);
		delete myThread;
		myThread = NULL;
	}
}

void CMutilThread2Dlg::ThreadFun_WaitForObject(CWinThread* pThread)
{
	if (pThread == NULL)
	{
		return;
	}

	while (1)
	{
		DWORD result;
		MSG msg;
		result = ::MsgWaitForMultipleObjects(1, &pThread->m_hThread, FALSE, INFINITE, QS_ALLINPUT);

		if (result == WAIT_OBJECT_0 + 1)
		{
			//响应windows消息
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
				if (msg.message == WM_QUIT)
					continue;
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			break;
		}
	}
}


void CMutilThread2Dlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	
	OnBnClickedBtnStop();

	CDialogEx::OnClose();
}
