
// MutilThread2Dlg.h: 头文件
//

#pragma once


// CMutilThread2Dlg 对话框
class CMutilThread2Dlg : public CDialogEx
{
// 构造
public:
	CMutilThread2Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MUTILTHREAD2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CWinThread* myThread;
	CCriticalSection g_ctrticalSection;
	BOOL isRunning;

	int sum;

	static UINT ThreadFun(LPVOID lpParam);
	static void ThreadFun_WaitForObject(CWinThread* pThread);

	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnBnClickedBtnSuspend();
	afx_msg void OnBnClickedBtnResume();
	afx_msg void OnBnClickedBtnShow();
	afx_msg void OnBnClickedBtnStop();
	afx_msg void OnClose();
};
