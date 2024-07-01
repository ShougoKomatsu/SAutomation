#include "stdafx.h"
#include "Thread.h"

#pragma once
#define MAX_VARIABLES (8)
extern int g_iVar[MAX_THREAD][MAX_VARIABLES];
int GetIntValue(int iScene, CString sArg);
int* GetIntValuePointer(int iScene, CString sArg);
