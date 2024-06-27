#include "stdafx.h"
#include "FlowManager.h"

int g_iNowLevel[MAX_THREAD];
int g_iProgramCounter[MAX_THREAD][MAX_LEVEL];


void ResetProgramCounter(int iScene)
{
	g_iNowLevel[iScene]=0;
	for(int i=0; i<MAX_LEVEL; i++)
	{
		g_iProgramCounter[iScene][i]=0;
	}
}