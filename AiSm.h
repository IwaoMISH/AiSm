// AiSm.h : AISM アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_AISM_H__F406AEA6_99AA_487A_B4F7_21A506FE80EF__INCLUDED_)
#define AFX_AISM_H__F406AEA6_99AA_487A_B4F7_21A506FE80EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル

/////////////////////////////////////////////////////////////////////////////
// CAiSmApp:
// このクラスの動作の定義に関しては AiSm.cpp ファイルを参照してください。
//

class CAiSmApp : public CWinApp
{
public:
	CAiSmApp();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CAiSmApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション

	//{{AFX_MSG(CAiSmApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_AISM_H__F406AEA6_99AA_487A_B4F7_21A506FE80EF__INCLUDED_)
