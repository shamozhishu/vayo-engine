
// ModelBuilder.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CModelBuilderApp: 
// 有关此类的实现，请参阅 ModelBuilder.cpp
//

class CModelBuilderApp : public CWinApp
{
public:
	CModelBuilderApp();

// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual BOOL OnIdle(LONG lCount);

// 实现
	DECLARE_MESSAGE_MAP()
private:
	CShellManager* m_pShellManager;
};

extern CModelBuilderApp theApp;
