#include "stdafx.h"
#include "Thread.h"
#include "ImgProc.h"
#include "common.h"


#pragma once
#define MAX_VARIABLES (8)
extern int g_iVar[MAX_THREAD][MAX_VARIABLES];
extern CString g_sVar[MAX_THREAD][MAX_VARIABLES];
extern ImgRGB g_imgRGB[MAX_THREAD][MAX_VARIABLES];


int GetIntValue(int iScene, CString sArg);
int* GetIntValuePointer(int iScene, CString sArg);

const CString GetStringValue(int iScene, CString sArg);
CString* GetStringValuePointer(int iScene, CString sArg);

ImgRGB* GetImgValuePointer(int iScene, CString sArg);
const ImgRGB* GetImgValuePointerConst(int iScene, CString sArg);

int IntAdd(int iScene, CString sArg1, CString sArg2);
int IntSub(int iScene, CString sArg1, CString sArg2);
int IntMult(int iScene, CString sArg1, CString sArg2);
int IntDiv(int iScene, CString sArg1, CString sArg2);
int IntAssign(int iScene, CString sArg, int iValue);
BOOL IsIntEqual(int iScene, CString sArg1, CString sArg2);

ReturnValue Flow_Assign(int iScene, CStringArray* saData);
ReturnValue Flow_IsIntEqual(int iScene, CStringArray* saData, CString* sReturnParam);

//int GetValueInt(int iScene, CString sArg);
void AssignInt(int iScene, CString sArg, int iInput);

const CString GetStrValue(int iScene, CString sArg);
void AssignString(int iScene, CString sArg, CString sInput);

const CString Int2Str(int iScene, CString sArg, CString sFormat);
int Str2Int(int iScene, CString sArg);

const CString NowDateTime(CString sArg);


#define VARIABLE_INT (0)
#define VARIABLE_ADD_INT (1)
#define VARIABLE_SUB_INT (2)
#define VARIABLE_MULT_INT (3)
#define VARIABLE_DIV_INT (4)

#define VARIABLE_STR (100)
#define VARIABLE_COMBINE_STR (101)
#define VARIABLE_INT2STR (102)
#define VARIABLE_NOW_DATE_TIME (103)

#define VARIABLE_IMG (200)
