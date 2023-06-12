#include "stdafx.h"

extern BOOL g_bHalt;
#define MAX_THREAD (10)

extern HANDLE g_hThread[MAX_THREAD];
extern CString g_sFilePath[MAX_THREAD];
DWORD WINAPI GetKeyThread(LPVOID arg);

DWORD WINAPI GetStepKeyThread(LPVOID arg);
DWORD WINAPI CommandThread(LPVOID arg);
