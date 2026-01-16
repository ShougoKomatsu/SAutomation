#include "stdafx.h"
#include "Common.h"
#define MAX_SUBBUF 100
#define MSG_LEN    256
extern int g_iWriteLogPeriodMilliSec;
extern int g_iCheckLogPeriodMilliSec;

extern BOOL g_bEndLogThread;
extern BOOL g_bClearFile[MAX_THREAD];
extern BOOL g_bReadyToLog;
BOOL SetLogQue(int iScene, CString sData);
DWORD WINAPI LoggerThread(LPVOID);