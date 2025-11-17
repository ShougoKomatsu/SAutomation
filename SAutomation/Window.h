#pragma once
#include "stdafx.h"

#include "ImgProc.h"
#include "Automation.h"

#define MAX_WINDOW_HANDLE (4096)
BOOL isProcessExist(CString sExePath);

ReturnValue RunExe(CString sExePath);
ReturnValue KillExe(CString sDir, int iScene, CStringArray* saData);
ReturnValue Maximize();
ReturnValue RunExe2(CString sExePath, HWND* hwnd);

ReturnValue Minimize();

BOOL CALLBACK EnumWindowsFunc(HWND hWnd, LPARAM lParam);
ReturnValue SetWindowForward(CString sDir, int iScene, CStringArray* saData);
ReturnValue WindowSize(CString sDir, int iScene, CStringArray* saData);
ReturnValue WindowPos(CString sDir, int iScene, CStringArray* saData);

BOOL GetWindowNameList(CStringArray* caNames);
BOOL GetWindowHandleByName(CString sTargetName, HWND* hwnd, BOOL bPartialMatch=TRUE);
BOOL GetWindowRectByName(CString sTargetName, RECT* rect, BOOL bPartialMatch = TRUE);
BOOL GetWindowHandleByProcessID(DWORD dwTargetID, HWND* hwnd);
BOOL GetProcessIDByWindowHandle(HWND hwnd,DWORD* dwProcessID);

ReturnValue SetWindowAttribute(CString sDir, int iScene, CStringArray* saData);

const CString GetForegroundWindowName();
const CString GetForegroundWindowClassName();


BOOL GetForegroundWindowPos(int* iLeft, int* iTop, int* iWidth, int* iHeight);
int GetDlgItem_My(CString sText, int iRank);
BOOL GetWindowRect_My(UINT iID, CRect* rect);
ReturnValue ListDlgItems();

ReturnValue SendMessage_My(CString sDir, int iScene, CStringArray* saData);