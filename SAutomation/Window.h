#include "stdafx.h"


#define MAX_WINDOW_HANDLE (4096)
BOOL isProcessExist(CString sExePath);

int RunExe(CString sExePath);
int Maximize();

int Minimize();

BOOL CALLBACK EnumWindowsFunc(HWND hWnd, LPARAM lParam);
int SetWindowForward(CString sTargetName);
int WindowSize(CStringArray* saData);
int WindowPos(CStringArray* saData);

BOOL GetWindowNameList(CStringArray* caNames);
BOOL GetHandleByName(CString sTargetName, HWND* hwnd, BOOL bPartialMatch=TRUE);