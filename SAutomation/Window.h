#pragma once
#include "stdafx.h"

#include "ImgProc.h"
#include "Automation.h"

#define MAX_WINDOW_HANDLE (4096)
BOOL isProcessExist(CString sExePath);

ReturnValue RunExe(CString sExePath);
ReturnValue Maximize();

ReturnValue Minimize();

BOOL CALLBACK EnumWindowsFunc(HWND hWnd, LPARAM lParam);
ReturnValue SetWindowForward(CString sTargetName);
ReturnValue WindowSize(int iScene, CStringArray* saData);
ReturnValue WindowPos(int iScene, CStringArray* saData);

BOOL GetWindowNameList(CStringArray* caNames);
BOOL GetHandleByName(CString sTargetName, HWND* hwnd, BOOL bPartialMatch=TRUE);
BOOL GetWindowRectByName(CString sTargetName, RECT* rect, BOOL bPartialMatch = TRUE);


const CString GetForegroundWindowName();
const CString GetForegroundWindowClassName();


BOOL GetForegroundWindowPos(int* iLeft, int* iTop, int* iWidth, int* iHeight);
int GetDlgItem_My(CString sText, int iRank);
BOOL GetWindowRect_My(UINT iID, CRect* rect);
ReturnValue ListDlgItems();