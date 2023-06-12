
// SAutomation.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです。
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CSAutomationApp:
// このクラスの実装については、SAutomation.cpp を参照してください。
//

class CSAutomationApp : public CWinApp
{
public:
	CSAutomationApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CSAutomationApp theApp;