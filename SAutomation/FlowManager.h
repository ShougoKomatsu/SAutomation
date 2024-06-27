#include "stdafx.h"
#include "thread.h"
#pragma once

#define MAX_LEVEL (1024)
extern int g_iNowLevel[MAX_THREAD];
extern int g_iProgramCounter[MAX_THREAD][MAX_LEVEL];

void ResetProgramCounter(int iScene);

int SearchLable(CStringArray* saData, CString sLabel, int iLog,  CStdioFile* cf);
int SearchSubRoutine(CStringArray* saData, CString sLabel, int iLog, CStdioFile* cf);
