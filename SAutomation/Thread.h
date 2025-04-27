#pragma once
#include "stdafx.h"

extern BOOL g_bHalt;
#define MAX_EX_THREAD (16)
#define MAX_NORMAL_THREAD (64)
#define MAX_THREAD (MAX_NORMAL_THREAD+MAX_EX_THREAD)

extern HANDLE g_hThread[MAX_THREAD];
extern CString g_sFilePath[MAX_THREAD];
extern int g_iLogLevel[MAX_THREAD];

extern CString g_sCommand[MAX_THREAD];
extern long g_lLockCommandDisplay;
DWORD WINAPI GetKeyThread(LPVOID arg);

DWORD WINAPI GetStepKeyThread(LPVOID arg);
DWORD WINAPI CommandThread(LPVOID arg);

#define PARAM_LOGLEVEL_SHIFT (0)
#define PARAM_LOGLEVEL_MASK (0x07)

#define PARAM_SCENE_SHIFT (0)
#define PARAM_SCENE_MASK (0xFF)