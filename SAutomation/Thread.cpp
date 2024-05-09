#include "stdafx.h"
#include "Thread.h"
#include "Common.h"
#include "Automation.h"
#include "resource.h"


HANDLE g_hThread[MAX_THREAD];

int g_iSceneData[MAX_THREAD];


CString g_sFilePath[MAX_THREAD];

BOOL g_bHalt;
BOOL g_bSuspend = FALSE;
LONGLONG g_llStepIn = 0;
LONGLONG g_llStepOut = 1;


DWORD WINAPI GetKeyThread(LPVOID arg)
{
	short shSpace;
	short shCtrl;
	short shShift;
	while(1)
	{
		shShift = GetKeyState(VK_SHIFT);
		shCtrl = GetKeyState(VK_CONTROL);
		shSpace = GetKeyState(VK_SPACE);
		if((shSpace<0)&&(shShift<0)&&(shCtrl<0)) 
		{
			g_bSuspend = TRUE;  
		}
		else        	
		{
			g_bSuspend = FALSE;
		}
		Sleep(1);
	}

	return 0;
} 
DWORD WINAPI GetStepKeyThread(LPVOID arg)
{
	short shStep;
	short shCtrl;
	short shShift;
	while(1)
	{

		shShift = GetKeyState(VK_SHIFT);
		shCtrl = GetKeyState(VK_CONTROL);
		shStep = GetKeyState(0x53);
		if((shStep<0)&&(shShift<0)&&(shCtrl<0)) 
		{
			if(g_llStepOut==1){g_llStepIn=1;}
		}

		Sleep(1);
	}
	return 0;
} 


DWORD WINAPI CommandThread(LPVOID arg)
{
	HANDLE hGetKey;
	HANDLE hGetStepKey;
	DWORD dwThreadID;
	int* iSceneData;
	
	g_iC=g_iC+g_iOriginC;
	g_iR=g_iR+g_iOriginR;
	g_iOriginC=0;
	g_iOriginR=0;

	hGetKey = CreateThread(NULL, 0, GetKeyThread, NULL, 0, &dwThreadID);
	hGetStepKey = CreateThread(NULL, 0, GetStepKeyThread, NULL, 0, &dwThreadID);
	CStringArray saCommands;
	CString sErrorGotoLable;

	int iData;
	iData = *((int*)arg);
	(*(int*)arg) = 0;  

	int iScene;
	iScene = (iData&0x0F);
	BOOL bRet;

	bRet = ReadTextFile(g_sFilePath[iScene],&saCommands);
	if(bRet != TRUE)
	{
	g_iC=g_iC+g_iOriginC;
	g_iR=g_iR+g_iOriginR;
	g_iOriginC=0;
	g_iOriginR=0;
		PostMessage(g_hWnd,WM_DISP_STANDBY,iScene,0);
		TerminateThread(hGetKey, 0);
		TerminateThread(hGetStepKey, 0);
		return 0;
	}

	g_iSceneData[iScene]=iScene;
	iSceneData=&g_iSceneData[iScene];

	int iLoop;
	iLoop =(iData>>4)&0x01;
	int iLogLevel;
	iLogLevel = (iData>>6)&0x07;

	int iErrorTreat;
	iErrorTreat = ERROR_TREAT_END;
	int iListLength;
	int iRet;
	CString sLabel;
	BOOL bExit;
	StopWatch sw;
	CStdioFile cf;
	CString sFilePath;
	sFilePath.Format(_T("%s\\Log\\log%d.txt"), g_sDir, iScene);
	if(iLogLevel>=1)
	{
		BOOL bRet;
		bRet = cf.Open(sFilePath,CFile::modeCreate|CFile::modeWrite);
	}
	CString sWrite;
	while(1)
	{
		iListLength =(int) saCommands.GetCount();
		for(int i=0; i<iListLength; i++)
		{
			sWrite.Format(_T("%d "), i+1);
			if(iLogLevel>=1){cf.WriteString(sWrite);}
			bExit = FALSE;
			if(g_bHalt == TRUE)
			{
				if(iLogLevel>=1){cf.Close();}
				g_bHalt = FALSE;
	g_iC=g_iC+g_iOriginC;
	g_iR=g_iR+g_iOriginR;
	g_iOriginC=0;
	g_iOriginR=0;
				PostMessage(g_hWnd,WM_DISP_STANDBY,iScene,0);
				TerminateThread(hGetKey, 0);
				TerminateThread(hGetStepKey, 0);
				return 0;
			}

			sWrite.Format(_T("%s "), saCommands.GetAt(i));
			if(iLogLevel>=1){cf.WriteString(sWrite);}
			iRet = OperateCommand(iSceneData, &g_bHalt, &g_bSuspend, &g_llStepIn, saCommands.GetAt(i));
			sWrite.Format(_T("%d\n"), iRet);
			if(iLogLevel>=1){cf.WriteString(sWrite);}
			switch(iRet)
			{
			case RETURN_HALT:
				{
					if(iLogLevel>=1){cf.Close();}
					g_bHalt = FALSE;
	g_iC=g_iC+g_iOriginC;
	g_iR=g_iR+g_iOriginR;
	g_iOriginC=0;
	g_iOriginR=0;
					PostMessage(g_hWnd,WM_DISP_STANDBY,iScene,0);
					TerminateThread(hGetKey, 0);
					TerminateThread(hGetStepKey, 0);
					return 0;
				}
			case RETURN_NORMAL: {break;}
			case RETURN_END:{bExit=TRUE; break;}
			case RETURN_LABEL:{break;}
			case RETURN_ERROR_TREAT:
				{
					int iErrTreatRet = GetErroTreat(saCommands.GetAt(i), &sLabel);
					switch(iErrTreatRet)
					{
					case ERROR_TREAT_END:{iErrorTreat=ERROR_TREAT_END; break;}
					case ERROR_TREAT_GOTO:{iErrorTreat=ERROR_TREAT_GOTO; break;}
					case ERROR_TREAT_RESUME:{iErrorTreat=ERROR_TREAT_RESUME; break;}
					default:
						{
							if(iLogLevel>=1){cf.Close();}
							g_bHalt = FALSE;
	g_iC=g_iC+g_iOriginC;
	g_iR=g_iR+g_iOriginR;
	g_iOriginC=0;
	g_iOriginR=0;
							PostMessage(g_hWnd,WM_DISP_STANDBY,iScene,0);
							TerminateThread(hGetKey, 0);
							TerminateThread(hGetStepKey, 0);
							return 0;
						}
					}
					break;
				}
			case RETURN_FAILED:
				{
					sWrite.Format(_T("iErrorTreat = %d %s\n"), iErrorTreat, sLabel);
					if(iLogLevel>=1){cf.WriteString(sWrite);}
					if(iErrorTreat==ERROR_TREAT_RESUME){break;}
					if(iErrorTreat==ERROR_TREAT_GOTO)
					{
						PerseLabelFromGotoStatement(saCommands.GetAt(i),&sLabel);
						int iLabel;
						iLabel = SearchLable(&saCommands,sLabel, iLogLevel, &cf);
						sWrite.Format(_T("iLabel = %d\n"), iLabel);
						if(iLogLevel>=1){cf.WriteString(sWrite);}
						if(iLabel >= 0){i=iLabel-1;break;}
					}
					g_bHalt = FALSE;
	g_iC=g_iC+g_iOriginC;
	g_iR=g_iR+g_iOriginR;
	g_iOriginC=0;
	g_iOriginR=0;
					PostMessage(g_hWnd,WM_DISP_STANDBY,iScene,0);
					TerminateThread(hGetKey, 0);
					TerminateThread(hGetStepKey, 0);
					return 0;
				}
			case RETURN_GOTO:
				{
					PerseLabelFromGotoStatement(saCommands.GetAt(i),&sLabel);
					int iLabel;
					iLabel = SearchLable(&saCommands,sLabel, iLogLevel, &cf);
					if(iLabel >= 0){i=iLabel-1;break;}

					if(iLogLevel>=1){cf.Close();}
					g_bHalt = FALSE;
	g_iC=g_iC+g_iOriginC;
	g_iR=g_iR+g_iOriginR;
	g_iOriginC=0;
	g_iOriginR=0;
					PostMessage(g_hWnd,WM_DISP_STANDBY,iScene,0);
					TerminateThread(hGetKey, 0);
					TerminateThread(hGetStepKey, 0);
					return 0;
				}
			}
			g_llStepOut=1;
			g_llStepIn=0;
			if(bExit==TRUE){break;}
		}
		if(iLoop==0){break;}
	}
	if(iLogLevel==1){cf.Close();}
	g_iC=g_iC+g_iOriginC;
	g_iR=g_iR+g_iOriginR;
	g_iOriginC=0;
	g_iOriginR=0;
	PostMessage(g_hWnd,WM_DISP_STANDBY,iScene,0);
	TerminateThread(hGetKey, 0);
	TerminateThread(hGetStepKey, 0);
	return 0;
}