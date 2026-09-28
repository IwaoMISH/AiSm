// **************************************************************************
//  @file       AS_FNC_M.INC
//  @brief      Minimum 版ファイルマージツール ドロップファイル処理
//
//  @author     Iwao (https://mish.work/)
//  @date       2026-06-08
//
//  @modify
//  2026-06-05  新規作成
//  2026-06-08  出力ファイル名の変更
//
//  @disclaimer
//  本コードの使用により生じたいかなる損害についても著作者は責任を負いません
//  引用時は上記 URL を明記してください
//
//  (C) 2026 Iwao. All Rights Reserved.
// **************************************************************************

#pragma     once

#ifdef      _MSC_VER
	#pragma warning (disable    :   4786)
#endif

#include    <string>
#include    <vector>
#include    <fstream>
#include    <windows.h>
#include    <shellapi.h>

#include    "i_types.inc"

////
// **************************************************************************
//  ANSI 文字列に変換
//  作成日    :    2026-06-05
// **************************************************************************
inline	std::string		to_MBs	(LPCTSTR str)
{
	std::string	mb_str ;
	#ifdef _UNICODE
	{
		int nLen = 	::WideCharToMultiByte(CP_ACP, 0, str, -1, NULL,      0,    NULL, NULL) ;
	//	std::string v_str(nLen) ;
		std::string v_str ;	v_str.resize(nLen) ;
					::WideCharToMultiByte(CP_ACP, 0, str, -1, &v_str[0], nLen, NULL, NULL) ;
		mb_str = v_str ;
		}
	#else
	{
		mb_str = str ;
		}
	#endif
	return	mb_str ;
	}

////
// **************************************************************************
//  出力先の取得
//  作成日    :    2026-06-05
// **************************************************************************
inline	tstring	AS_GetOutDir	(void)
{
	TCHAR szTempPath[MAX_PATH] = { 0 } ;
	::GetTempPath(MAX_PATH, szTempPath) ;

	tstring	outDir  = szTempPath ;
			outDir += _T("AiSm_M\\") ;
	return	outDir ;
	}

////
// **************************************************************************
//  バイナリファイル判定
//  作成日    :    2026-06-05
// **************************************************************************
inline bool AS_IsBinaryFile(LPCTSTR pathName)
{
	if (pathName == NULL)	{
		return false ;
		}

	// 1. ファイルをバイナリ読み込みモードで安全に開く
	std::ifstream ifs ;
	std::string	s_pathName = ::to_MBs(pathName) ;

	ifs.open(s_pathName.c_str(), std::ios::in | std::ios::binary) ;
	if (!ifs.is_open())	{
		return false ;
		}

	// 2. 先頭から最大 1024 バイトを読み込む
	char buffer[1024] = { 0 } ;
	ifs.read(buffer, sizeof(buffer)) ;
	std::streamsize readSize = ifs.gcount() ;
	ifs.close() ;

	if (readSize <= 0)	{
		return false ; // 空ファイルはテキスト扱いとする
		}

	// 3. バッファ内にヌル文字（0x00）があるかをスキャン
	for (std::streamsize i = 0 ; i < readSize ; ++i)	{
		if (buffer[i] == '\0')		{
			return true ; // ヌル文字が見つかったらバイナリ
			}
		}

	return false ; // 見つからなければテキスト
	}

////
// **************************************************************************
//  ドロップファイル群のパス蓄積
//  作成日    :    2026-06-05
// **************************************************************************
inline v_tstring	DropFiles	(HDROP hDropInfo)
{
	v_tstring dropFiles ;
	UINT nFiles = ::DragQueryFile(hDropInfo, (UINT)-1, NULL, 0) ;

	for (UINT index = 0; index < nFiles; index++)	{
		UINT len = ::DragQueryFile(hDropInfo, index, NULL, 0) ;
		len += 1 ;

		tstring dropFile ;
		dropFile.resize(len, 0) ;
		::DragQueryFile(hDropInfo, index, &dropFile[0], len) ;

		dropFiles.push_back(dropFile.c_str()) ;
		}

	return	dropFiles ;
	}

////
// **************************************************************************
//  数値の文字列変換（桁埋め付き）
//  作成日    :    2026-06-08
// **************************************************************************
inline	tstring		IntToTString(int val, int digits)
{
	TCHAR szBuf[16];
	//	_itot は可変長引数ではなく、単なる文字列変換関数です
	::_itot(val, szBuf, 10);
	tstring s = szBuf;
	//	桁が足りない場合のゼロ埋め処理（シンプルに記述）
	while ((int)s.length() < digits)   {
		s = _T("0") + s;
		}
    return s;
	}

////
// **************************************************************************
//  現在の時刻からユニークな文字列を作成
//  作成日    :    2026-06-08
// **************************************************************************
inline	tstring	GenerateUniqueFileName(LPCTSTR name)
{
	SYSTEMTIME st;
	::GetLocalTime(&st);
    tstring strName = name ;
	{
			strName += _T("_") ;
			strName += IntToTString(st.wYear,   4);
			strName += IntToTString(st.wMonth,  2);
			strName += IntToTString(st.wDay,    2);
			strName += _T("_");
			strName += IntToTString(st.wHour,   2);
			strName += IntToTString(st.wMinute, 2);
			strName += IntToTString(st.wSecond, 2);
			strName += _T(".txt");
		}
	return strName;
	}

////
// **************************************************************************
//  ファイルマージ結合処理実体	Minimum 版
//  作成日    :    2026-06-05
// **************************************************************************
inline bool AS_MergeFiles(c_v_tstring& srcFiles)
{
	//	要素数チェック (2ファイル未満はマージ不可)
	if (srcFiles.size() < 2)	{
		return false ;
		}

	tstring outDir = ::AS_GetOutDir() ;
	{
	//	マージ専用の一時フォルダを作成 (存在しなければ自動掘削)
		::CreateDirectory(outDir.c_str(), NULL) ;
		}

	tstring outFilePath ;
	{
	//	1つ目のファイルパスから親フォルダ名を抽出して出力ファイル名を決定
		tstring firstPath = srcFiles[0] ;
		
		// 末尾のファイル名を除去するために最後の "\" を検索
		size_t lastSlash = firstPath.find_last_of(_T("\\/")) ;
		if (lastSlash == tstring::npos)	{
			return false ;
			}
		tstring parentDir = firstPath.substr(0, lastSlash) ;

		// さらにその手前の "\" を検索して最下層の親フォルダ名を切り出す
		size_t prevSlash = parentDir.find_last_of(_T("\\/")) ;
		tstring folderName ;
		if (prevSlash != tstring::npos)	{
			folderName = parentDir.substr(prevSlash + 1) ;
			}
		else	{
			folderName = _T("merged_files") ; // 万が一切り出せなかった場合の安全なフォールバック
			}

		// 最終出力ファイルパスの組み立て (%TMP%\AiSm_M\〇〇.txt)
	//	outFilePath = outDir + folderName + _T(".txt") ;
		outFilePath = outDir + ::GenerateUniqueFileName(folderName.c_str()) ;
		}
	//	出力ファイルをストリームで開く (バイナリモードで新規作成)
	bool	hasMergedAtLeastOne = false ;
	{
		std::ofstream ofs ;
		std::string	s_outFilePath = ::to_MBs(outFilePath.c_str()) ;

		ofs.open(s_outFilePath.c_str(), std::ios::out | std::ios::binary | std::ios::trunc) ;
		if (!ofs.is_open())	{
			return false ;
			}

	//	入力ファイルを順次読み込んで一気に結合
		for (size_t index = 0; index < srcFiles.size(); index++)	{

			tstring  filePath = srcFiles[index] ;

			//	バイナリファイルは安全のためにスキップ
			if (::AS_IsBinaryFile(filePath.c_str()))		{
				continue ;
				}

			std::ifstream ifs ;
			std::string	s_filePath = ::to_MBs(filePath.c_str()) ;
			ifs.open(s_filePath.c_str(), std::ios::in | std::ios::binary) ;
			if (ifs.is_open())		{

				{
					// フルパスからファイル名のみを抽出する
					tstring fileName ;
					{
						size_t lastSlash = filePath.find_last_of(_T("\\/")) ;
						if (lastSlash != tstring::npos)	{
							fileName = filePath.substr(lastSlash + 1) ;
							}
						else	{
							fileName = filePath ;
							}
						}

				// 可変引数やストリームを使わず tstring の加算のみで安全にヘッダーを組み立て
					{
						tstring headerStr  = _T("=============================================================================\r\n") ;
								headerStr += _T("[FILE] ") + fileName +                                                   _T("\r\n") ;
								headerStr += _T("=============================================================================\r\n\r\n") ;

						// _UNICODE 時は char 配列へ簡易キャスト変換、_MBCS 時はそのまま流し込み
						#ifdef _UNICODE
							int nLen = ::WideCharToMultiByte(CP_ACP, 0, headerStr.c_str(), -1, NULL, 0, NULL, NULL) ;
							std::vector<char> vBuffer(nLen) ;
							::WideCharToMultiByte(CP_ACP, 0, headerStr.c_str(), -1, &vBuffer[0], nLen, NULL, NULL) ;
							ofs.write(&vBuffer[0], nLen - 1) ;
						#else
							ofs << headerStr.c_str() ;
						#endif
						}
					}

				// ファイル丸ごと出力ストリームへ流し込み
				ofs << ifs.rdbuf() ;
				ifs.close() ;

				// ファイル境界に改行コードを挿入
				ofs << "\r\n\r\n" ;		//	char
				hasMergedAtLeastOne = true ;
				}
			}

		ofs.close() ;
		}

	return	hasMergedAtLeastOne ;
	}

