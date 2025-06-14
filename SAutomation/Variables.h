#pragma once

#include "stdafx.h"
#include "Thread.h"
#include "ImgProc.h"
#include "common.h"
#include "Variables_Byte.h"
struct Point
{
	int r;
	int c;
	Point(){r=0; c=0;}
	Point(Point* pPointIn){r=pPointIn->r; c=pPointIn->c;}
	Point( int cIn,int rIn){Set(cIn,rIn);}
	void Set(int cIn,int rIn){r=rIn; c=cIn;}
	Point operator = (Point pIn){Set(pIn.c,pIn.r);}
};

#define MAX_VARIABLES (8)
extern int g_iVar[MAX_THREAD][MAX_VARIABLES];
extern CString g_sVar[MAX_THREAD][MAX_VARIABLES];
extern ImgRGB g_imgRGB[MAX_THREAD][MAX_VARIABLES];
extern Point g_point[MAX_THREAD][MAX_VARIABLES];
extern Object g_object[MAX_THREAD][MAX_VARIABLES];
extern CRect g_rect[MAX_THREAD][MAX_VARIABLES];

extern ByteVector g_bytes[MAX_THREAD][MAX_VARIABLES];

extern Camera g_camera;


ReturnValue Flow_Assign(CString sDir, int iScene, CStringArray* saData);
ReturnValue Flow_AreStrEqual(CString sDir, int iScene, CStringArray* saData, CString* sReturnParam);
ReturnValue Flow_Compare(CString sDir, int iScene, CStringArray* saData, CString* sReturnParam);


ReturnValue MessageBox_My(CString sDir, int iScene, CStringArray* saData);


#define VARIABLE_UNDEFINED (-1)
#define VARIABLE_INT (0)
#define VARIABLE_ADD_INT (1)
#define VARIABLE_SUB_INT (2)
#define VARIABLE_MULT_INT (3)
#define VARIABLE_DIV_INT (4)
#define VARIABLE_IMG_WIDTH (5)
#define VARIABLE_IMG_HEIGHT (6)
#define VARIABLE_ADD_ITSELF_INT (7)
#define VARIABLE_SUB_ITSELF_INT (8)
#define VARIABLE_MULT_ITSELF_INT (9)
#define VARIABLE_DIV_ITSELF_INT (10)
#define VARIABLE_IMG_VALUE (11)
#define VARIABLE_DLG_ITEM (12)
#define VARIABLE_RECT_WIDTH (13)
#define VARIABLE_RECT_HEIGHT (14)
#define VARIABLE_RECT_LEFT (15)
#define VARIABLE_RECT_TOP (16)
#define VARIABLE_RECT_RIGHT (17)
#define VARIABLE_RECT_BOTTOM (18)
#define VARIABLE_INT_FOREGROUND_WINDOW (19)


#define VARIABLE_STR (100)
#define VARIABLE_COMBINE_STR (101)
#define VARIABLE_INT2STR (102)
#define VARIABLE_NOW_DATE_TIME (103)
#define VARIABLE_FOREGROUND_WINDOW_NAME (104)
#define VARIABLE_STR_LEFT (105)
#define VARIABLE_STR_RIGHT (106)
#define VARIABLE_STR_MID (107)
#define VARIABLE_FOREGROUND_WINDOW_CLASS_NAME (108)
#define VARIABLE_STR_LEN (109)
#define VARIABLE_STR2INT (110)

#define VARIABLE_IMG (200)
#define VARIABLE_CROP_IMAGE (201)
#define VARIABLE_SCREENSHOT (202)
#define VARIABLE_IMG_DECOMPOSE (203)
#define VARIABLE_IMG_REDUCE_DOMAIN (204)
#define VARIABLE_SCREENSHOT_FOREGROUND_WINDOW (205)

#define VARIABLE_POINT (300)
#define VARIABLE_POINT_GET_R (301)
#define VARIABLE_POINT_GET_C (302)
#define VARIABLE_POINT_SET_R (303)
#define VARIABLE_POINT_SET_C (304)
#define VARIABLE_POINT_DIRECT (305)
#define VARIABLE_POINT_MOUSE_POS (306)
#define VARIABLE_POINT_OBJECT_CENTER (307)
#define VARIABLE_POINT_FOREGROUND_WINDOW_LU (308)
#define VARIABLE_POINT_FOREGROUND_WINDOW_RD (309)
#define VARIABLE_POINT_SEARCH_RESULT (310)

#define VARIABLE_INPUT (400)
#define VARIABLE_CLIPBOARD (401)
#define VARIABLE_CLIPBOARD_FILE_PATH (402)
#define VARIABLE_CLIPBOARD_FILE_NAME (403)
#define VARIABLE_CLIPBOARD_FILE_CREATIONTIME (404)
#define VARIABLE_CLIPBOARD_FILE_LASTACCESSTIME (405)
#define VARIABLE_CLIPBOARD_FILE_LASTWRITETIME (406)

#define VARIABLE_OBJECT (500)
#define VARIABLE_OBJECT_THRESHLD (501)
#define VARIABLE_OBJECT_CONNECTION (502)
#define VARIABLE_OBJECT_SELECT_OBJ (503)
#define VARIABLE_OBJECT_SELECT_SHAPE (504)
#define VARIABLE_OBJECT_SORT_REGION (505)
#define VARIABLE_OBJECT_GEN_RECTANGLE1 (506)

#define VARIABLE_CAMERA (600)
#define VARIABLE_CAMERA_OPEN (601)
#define VARIABLE_CAMERA_CLOSE (602)
#define VARIABLE_CAMERA_GRAB (603)

#define VARIABLE_RECT (700)
#define VARIABLE_RECT_FOREGROUND_WINDOW (701)
#define VARIABLE_RECT_DLG_ITEM (702)


#define VARIABLE_BYTES (800)

#define VARIABLE_SELF_SRC_NONE (0)
#define VARIABLE_SELF_SRC_ADD (1)
#define VARIABLE_SELF_SRC_SUB (2)
#define VARIABLE_SELF_SRC_MULT (3)
#define VARIABLE_SELF_SRC_DIV (4)


#include "Variables_Int.h"
#include "Variables_Obj.h"
#include "Variables_Img.h"
#include "Variables_String.h"
BOOL GetRectData(CString sDir, int iScene, CStringArray* saData, int iStartIndex, int* iR0, int* iC0, int* iR1, int* iC1, int* iNextIndex);
int GetOperandType(CString sDataLine);