#include "stdafx.h"
#include "Thread.h"
#include "ImgProc.h"
#include "common.h"


#pragma once
struct Point
{
	int r;
	int c;
	Point(){r=0; c=0;}
	Point(Point* pointIn){r=pointIn->r; c=pointIn->c;}
	Point(int rIn, int cIn){Set(rIn, cIn);}
	void Set(int rIn, int cIn){r=rIn; c=cIn;}
	Point operator = (Point pIn){Set(pIn.r, pIn.c);}
};

#define MAX_VARIABLES (8)
extern int g_iVar[MAX_THREAD][MAX_VARIABLES];
extern CString g_sVar[MAX_THREAD][MAX_VARIABLES];
extern ImgRGB g_imgRGB[MAX_THREAD][MAX_VARIABLES];
extern Point g_point[MAX_THREAD][MAX_VARIABLES];

int GetIntValue(int iScene, CString sArg);
int* GetIntValuePointer(int iScene, CString sArg);

const CString GetStrValue(int iScene, CString sArg);
CString* GetStrValuePointer(int iScene, CString sArg);

ImgRGB* GetImgValuePointer(int iScene, CString sArg);
const ImgRGB* GetImgValuePointerConst(int iScene, CString sArg);


Point* GetPointValuePointer(int iScene, CString sArg);
Point GetPointValue(int iScene, CString sArg);

int IntAdd(int iScene, CString sArg1, CString sArg2);
int IntSub(int iScene, CString sArg1, CString sArg2);
int IntMult(int iScene, CString sArg1, CString sArg2);
int IntDiv(int iScene, CString sArg1, CString sArg2);
BOOL IsIntEqual(int iScene, CString sArg1, CString sArg2);

ReturnValue Flow_Assign(int iScene, CStringArray* saData);
ReturnValue Flow_IsIntEqual(int iScene, CStringArray* saData, CString* sReturnParam);

void AssignInt(int iScene, CString sArg, int iInput);
void AssignString(int iScene, CString sArg, CString sInput);

const CString Int2Str(int iScene, CString sArg, CString sFormat);
int Str2Int(int iScene, CString sArg);

const CString NowDateTime(CString sArg);


#define VARIABLE_INT (0)
#define VARIABLE_ADD_INT (1)
#define VARIABLE_SUB_INT (2)
#define VARIABLE_MULT_INT (3)
#define VARIABLE_DIV_INT (4)
#define VARIABLE_IMG_WIDTH (5)
#define VARIABLE_IMG_HEIGHT (6)

#define VARIABLE_STR (100)
#define VARIABLE_COMBINE_STR (101)
#define VARIABLE_INT2STR (102)
#define VARIABLE_NOW_DATE_TIME (103)

#define VARIABLE_IMG (200)
#define VARIABLE_CROP_IMAGE (201)
#define VARIABLE_SCREENSHOT (202)

#define VARIABLE_POINT (300)
#define VARIABLE_POINT_GET_R (301)
#define VARIABLE_POINT_GET_C (302)
#define VARIABLE_POINT_SET_R (303)
#define VARIABLE_POINT_SET_C (304)
#define VARIABLE_POINT_DIRECT (305)
#define VARIABLE_POINT_MOUSE_POS (306)