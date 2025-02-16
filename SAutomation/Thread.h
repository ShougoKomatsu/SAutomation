#include "stdafx.h"

extern BOOL g_bHalt;
#define MAX_THREAD (64)

extern HANDLE g_hThread[MAX_THREAD];
extern CString g_sFilePath[MAX_THREAD];
extern int g_iLogLevel[MAX_THREAD];


DWORD WINAPI GetKeyThread(LPVOID arg);

DWORD WINAPI GetStepKeyThread(LPVOID arg);
DWORD WINAPI CommandThread(LPVOID arg);

#define PARAM_LOGLEVEL_SHIFT (0)
#define PARAM_LOGLEVEL_MASK (0x07)

#define PARAM_SCENE_SHIFT (0)
#define PARAM_SCENE_MASK (0x2F)