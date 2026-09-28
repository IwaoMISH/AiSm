// **************************************************************************
//  @file       AISMDLG.CPP
//  @brief      ファイルマージツール メインダイアログクラス実装
//
//  @author     Iwao (https://mish.work/)
//  @date       2026-06-08
//
//  @modify
//  2026-06-05  新規作成
//  2026-06-08  リストボックスやクリアを追加
//
//  @disclaimer
//  本コードの使用により生じたいかなる損害についても著作者は責任を負いません
//  引用時は上記 URL を明記してください
//
//  (C) 2026 Iwao. All Rights Reserved.
// **************************************************************************

#include "stdafx.h"
#include "AiSm.h"
#include "AiSmDlg.h"

#include	"AS_Fnc_M.inc"
#include	<algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// アプリケーションのバージョン情報で使われている CAboutDlg ダイアログ

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ダイアログ データ
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// メッセージ ハンドラがありません。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAiSmDlg ダイアログ

CAiSmDlg::CAiSmDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAiSmDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAiSmDlg)
		// メモ: この位置に ClassWizard によってメンバの初期化が追加されます。
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAiSmDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAiSmDlg)
	DDX_Control(pDX, IDC_LIST_FILES, m_CtrlListFiles);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAiSmDlg, CDialog)
	//{{AFX_MSG_MAP(CAiSmDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_MERGE, OnMerge)
	ON_BN_CLICKED(IDC_LIST_CLEAR, OnListClear)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAiSmDlg メッセージ ハンドラ

BOOL CAiSmDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// "バージョン情報..." メニュー項目をシステム メニューへ追加します。

	// IDM_ABOUTBOX はコマンド メニューの範囲でなければなりません。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);			// 大きいアイコンを設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンを設定
	
	// TODO: 特別な初期化を行う時はこの場所に追加してください。
	
	return TRUE;  // TRUE を返すとコントロールに設定したフォーカスは失われません。
}

void CAiSmDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// もしダイアログボックスに最小化ボタンを追加するならば、アイコンを描画する
// コードを以下に記述する必要があります。MFC アプリケーションは document/view
// モデルを使っているので、この処理はフレームワークにより自動的に処理されます。

void CAiSmDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画用のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// クライアントの矩形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンを描画します。
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CAiSmDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


////
// **************************************************************************
//  ファイルドロップハンドラ
//  作成日    :    2026-06-05
//  変更日    :    2026-06-08
// **************************************************************************
void CAiSmDlg::OnDropFiles(HDROP hDropInfo)
{
	{	//	ドロップされたファイルを格納
		v_tstring	dropFiles = ::DropFiles(hDropInfo) ;
		SrcFiles.insert(SrcFiles.end(),dropFiles.begin(),dropFiles.end()) ;
		}
	{	//	ソートと重複排除
		std::sort(SrcFiles.begin(), SrcFiles.end());
		SrcFiles.erase(std::unique(SrcFiles.begin(), SrcFiles.end()), SrcFiles.end());
		}
	{	//	リストボックスにファイル名を設定
		m_CtrlListFiles.ResetContent() ;
		for (size_t index=0 ; index<SrcFiles.size() ; index++) 	{
			tstring	file = SrcFiles[index] ;
			size_t	lastSlash = file.find_last_of(_T("\\/")) ;
			if (lastSlash != tstring::npos)	{
					file = file.substr(lastSlash+1) ;
				}
			m_CtrlListFiles.AddString(file.c_str()) ;
			}
		}
	//	基底クラスにバトンを渡し メモリハンドルを安全に解放
	CDialog::OnDropFiles(hDropInfo) ;
	}

////
// **************************************************************************
//  マージ実行ボタンクリックハンドラ
//  作成日    :    2026-06-05
// **************************************************************************
void CAiSmDlg::OnMerge() 
{
	//	マージ結合処理の実行
	bool isSuccess = false ;
	{
		isSuccess = ::AS_MergeFiles(SrcFiles) ;
		}

	//	マージ成功時 出力先フォルダ（%TMP%\AiSm_M\）をエクスプローラで自動展開
	if (isSuccess)	{
		tstring outDir = ::AS_GetOutDir() ;
		// エクスプローラを起動して対象フォルダを開く
		::ShellExecute(this->m_hWnd, _T("open"), _T("explorer.exe"), outDir.c_str(), NULL, SW_SHOWNORMAL) ;
		}
	}

////
// **************************************************************************
//  クリア
//  作成日    :    2026-06-08
// **************************************************************************
void CAiSmDlg::OnListClear() 
{
	m_CtrlListFiles.ResetContent();
	SrcFiles.clear() ;
	}
