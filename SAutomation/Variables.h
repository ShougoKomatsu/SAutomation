#include "stdafx.h"
#include "Thread.h"

#pragma once
#define MAX_VARIABLES (8)
extern int g_iVar[MAX_THREAD][MAX_VARIABLES];
int GetIntValue(int iScene, CString sArg);
int* GetIntValuePointer(int iScene, CString sArg);

int IntAdd(int iScene, CString sArg1, CString sArg2);
int IntSub(int iScene, CString sArg1, CString sArg2);
int IntMult(int iScene, CString sArg1, CString sArg2);
int IntDiv(int iScene, CString sArg1, CString sArg2);
int IntAssign(int iScene, CString sArg, int iValue);
BOOL IsIntEqual(int iScene, CString sArg1, CString sArg2);
