#include "stdafx.h"
#include "Logger.h"
#include "Common.h"
BOOL g_bClearFile[MAX_THREAD];
struct Message 
{
	int iScene;
	CString sLogText;
	void Copy(const Message* mesIn)
	{
		this->iScene=mesIn->iScene;
		this->sLogText.Format(_T("%s"),(LPCTSTR)mesIn->sLogText);
	}
};

CRITICAL_SECTION csMainQue;
CRITICAL_SECTION csSubQue;

#define MAX_QUE (1024)
Message g_MainQue[MAX_QUE];
int g_iMainQuePos = 0;

Message g_SubQue[MAX_QUE];
int g_iSubQuePos = 0;

volatile LONG interlockFlag = 0;
volatile LONG doneFlag = 0;
BOOL g_bEndLogThread=FALSE;

HANDLE hEventMsg;
HANDLE hLogFile;



enum QueStatus
{
	QUE_LOCKED = -1,
	QUE_NO_QUE =0,
	QUE_POP_NORMAL = 1,
};

BOOL PushSub(const Message* mes) 
{
	BOOL bRet = TryEnterCriticalSection(&csSubQue);
	if(bRet != TRUE)
	{
		return FALSE;
	}

	if (g_iSubQuePos >= MAX_QUE) 
	{
		LeaveCriticalSection(&csSubQue);
		return FALSE;
    }
	g_SubQue[g_iSubQuePos].Copy(mes);
    g_iSubQuePos++;
    LeaveCriticalSection(&csSubQue);
    return TRUE;
}

BOOL PushMain(const Message* mes) 
{
    if(TryEnterCriticalSection(&csMainQue) != TRUE)
	{
		return PushSub(mes);
	}

    if (g_iMainQuePos >= MAX_QUE) 
	{
		BOOL bRet = PushSub(mes);
        LeaveCriticalSection(&csMainQue);
        return bRet;
    }

    g_MainQue[g_iMainQuePos].Copy(mes);
    g_iMainQuePos++;
    LeaveCriticalSection(&csMainQue);
    return TRUE;
}


QueStatus PopAllMain(Message* mes, int* iNum) 
{
	EnterCriticalSection(&csMainQue);
	int i=0;
	for(int i=0; i<g_iMainQuePos; i++)
	{
		mes[i].Copy(&(g_MainQue[i]));
	}
	*iNum=g_iMainQuePos;
	g_iMainQuePos=0;
	LeaveCriticalSection(&csMainQue);
	return QUE_POP_NORMAL;
}

QueStatus PopAllSub(Message* mes, int* iNum) 
{
	EnterCriticalSection(&csSubQue);
	int i=0;
	for(int i=0; i<g_iSubQuePos; i++)
	{
		mes[i].Copy(&(g_SubQue[i]));
	}
	*iNum=g_iSubQuePos;
	g_iSubQuePos=0;
	LeaveCriticalSection(&csSubQue);
	return QUE_POP_NORMAL;
}


BOOL SetLogQue(int iScene, CString sData)
{
	if(g_iLogLevel[iScene]<=0){return FALSE;}
	BOOL bRet;
	Message mes;
	mes.iScene=iScene;
	mes.sLogText.Format(_T("%s"), sData);
	bRet = PushMain(&mes);
    SetEvent(hEventMsg);
	return bRet;
}


DWORD WINAPI LoggerThread(LPVOID) 
{
    InitializeCriticalSection(&csMainQue);
    InitializeCriticalSection(&csSubQue);

	BOOL bNeedToWrite[MAX_THREAD]={FALSE};
	Message mesMain[MAX_QUE];
	Message mesSub[MAX_QUE];

	DWORD timeLastWrote = GetTickCount();
	while (1) 
	{
		int iMain;
		if(PopAllMain(mesMain,&iMain) != QUE_POP_NORMAL){break;}

		int iSub;
		if(PopAllSub(mesSub,&iSub) != QUE_POP_NORMAL){break;}
		
		for(int iScene=0; iScene<MAX_THREAD; iScene++)
		{
			bNeedToWrite[iScene]=FALSE;
		}

		for(int i=0; i<iMain; i++)
		{
			bNeedToWrite[mesMain[i].iScene]=TRUE;
		}

		for(int i=0; i<iSub; i++)
		{
			bNeedToWrite[mesSub[i].iScene]=TRUE;
		}

		for(int iScene=0; iScene<MAX_THREAD; iScene++)
		{
			if(g_iLogLevel[iScene]<=0){continue;}
			if(bNeedToWrite[iScene] != TRUE){continue;}
			if(g_bClearFile[iScene]==TRUE)
			{
				g_utfW[iScene].OpenUTFFile(g_sLogFilePath[iScene],_T("w, ccs=UTF-8"));
				g_bClearFile[iScene]=FALSE;
			}
			else
			{
				g_utfW[iScene].OpenUTFFile(g_sLogFilePath[iScene],_T("a, ccs=UTF-8"));
			}
		}
		for(int i=0; i<iMain; i++)
		{
			g_utfW[mesMain[i].iScene].WriteString(mesMain[i].sLogText);
		}

		for(int i=0; i<iSub; i++)
		{
			g_utfW[mesSub[i].iScene].WriteString(mesSub[i].sLogText);
		}

		for(int iScene=0; iScene<MAX_THREAD; iScene++)
		{
			if(g_iLogLevel[iScene]<=0){continue;}
			if(bNeedToWrite[iScene] != TRUE){continue;}
			g_utfW[iScene].CloseUTFFile();
		}

		while(1)
		{
			if(g_bEndLogThread==TRUE){break;}
			DWORD now = GetTickCount();
			if (now - timeLastWrote >= 1000) 
			{
				timeLastWrote = now;
				break;
			}
			Sleep(10);
		}
	}
    DeleteCriticalSection(&csMainQue);
    DeleteCriticalSection(&csSubQue);
	return 0;
}

