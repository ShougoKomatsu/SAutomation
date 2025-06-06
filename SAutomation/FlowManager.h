#pragma once
#include "stdafx.h"
#include "thread.h"
#include "Common.h"


#define MAX_LEVEL (1024)
extern int g_iNowLevel[MAX_THREAD];
extern int g_iProgramCounter[MAX_THREAD][MAX_LEVEL];

void ResetProgramCounter(CString sDir, int iScene);

int SearchLable(CStringArray* saData, CString sLabel, int iScene);
int SearchSubRoutine(CStringArray* saData, CString sLabel, int iScene);
