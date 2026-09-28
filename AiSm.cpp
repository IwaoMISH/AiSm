// AiSm.cpp : アプリケーション用クラスの定義を行います。
//

#include "stdafx.h"
#include "AiSm.h"
#include "AiSmDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAiSmApp

BEGIN_MESSAGE_MAP(CAiSmApp, CWinApp)
	//{{AFX_MSG_MAP(CAiSmApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAiSmApp クラスの構築

CAiSmApp::CAiSmApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// 唯一の CAiSmApp オブジェクト

CAiSmApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CAiSmApp クラスの初期化

BOOL CAiSmApp::InitInstance()
{
	// 標準的な初期化処理

	CAiSmDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	// ダイアログが閉じられてからアプリケーションのメッセージ ポンプを開始するよりは、
	// アプリケーションを終了するために FALSE を返してください。
	return FALSE;
}
