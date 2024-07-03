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

int Flow_AddInt(int iScene, CStringArray* saData);
int Flow_SubInt(int iScene, CStringArray* saData);
int Flow_MultInt(int iScene, CStringArray* saData);
int Flow_DivInt(int iScene, CStringArray* saData);
int Flow_Assign(int iScene, CStringArray* saData);
int Flow_IsIntEqual(int iScene, CStringArray* saData, CString* sReturnParam);
int GetValueInt(int iScene, CString sArg);
void AssignInt(int iScene, CString sArg, int iInput);

