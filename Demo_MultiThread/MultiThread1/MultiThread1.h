
// MultiThread1.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMultiThread1App: 
// �йش����ʵ�֣������ MultiThread1.cpp
//

class CMultiThread1App : public CWinApp
{
public:
	CMultiThread1App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMultiThread1App theApp;