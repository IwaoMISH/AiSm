// **************************************************************************
//  @file       AISMDLG.H
//  @brief      ファイルマージツール メインダイアログクラス定義
//
//  @author     Iwao (https://mish.work/)
//  @date       2026-06-05
//
//  @modify
//  2026-06-05  新規作成
//
//  @disclaimer
//  本コードの使用により生じたいかなる損害についても著作者は責任を負いません
//  引用時は上記 URL を明記してください
//
//  (C) 2026 Iwao. All Rights Reserved.
// **************************************************************************

#if !defined(AFX_AISMDLG_H__BF06874D_743F_4279_87CD_18735E21B795__INCLUDED_)
#define AFX_AISMDLG_H__BF06874D_743F_4279_87CD_18735E21B795__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include	"i_types.inc"

/////////////////////////////////////////////////////////////////////////////
// CAiSmDlg ダイアログ

class CAiSmDlg : public CDialog
{
// 構築
public:
	CAiSmDlg(CWnd* pParent = NULL);	// 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CAiSmDlg)
	enum { IDD = IDD_AISM_DIALOG };
	CListBox	m_CtrlListFiles;
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CAiSmDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	v_tstring SrcFiles;
	HICON m_hIcon;

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CAiSmDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnMerge();
	afx_msg void OnListClear();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_AISMDLG_H__BF06874D_743F_4279_87CD_18735E21B795__INCLUDED_)
