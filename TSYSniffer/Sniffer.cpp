// Sniffer.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "Sniffer.h"
#include "SnifferDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSnifferApp

BEGIN_MESSAGE_MAP(CSnifferApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CSnifferApp 构造

CSnifferApp::CSnifferApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CSnifferApp 对象

CSnifferApp theApp;

// CSnifferApp 初始化

BOOL CSnifferApp::InitInstance()
{

	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// 标准初始化

	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	CSnifferDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}


	return FALSE;
}
