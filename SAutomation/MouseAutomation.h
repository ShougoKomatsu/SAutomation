#pragma once
#include "stdafx.h"


#include "Automation.h"

#define COMMAND_MOUSE_MOVE (COMMAND_MOUSE+1)
#define COMMAND_MOUSE_L_DOWN (COMMAND_MOUSE+2)
#define COMMAND_MOUSE_L_UP (COMMAND_MOUSE+3)

#define COMMAND_MOUSE_R_DOWN (COMMAND_MOUSE+4)
#define COMMAND_MOUSE_R_UP (COMMAND_MOUSE+5)

#define COMMAND_WHEEL (COMMAND_MOUSE+6)

#define COMMAND_MOUSE_M_DOWN (COMMAND_MOUSE+7)
#define COMMAND_MOUSE_M_UP (COMMAND_MOUSE+8)

#define COMMAND_MOUSE_L_CLICK (COMMAND_MOUSE+100+1)
#define COMMAND_MOUSE_R_CLICK (COMMAND_MOUSE+100+2)

#define COMMAND_MOUSE_MOVE_INCL (COMMAND_MOUSE+100+3)
#define COMMAND_MOUSE_MOVE_TO_IMG (COMMAND_MOUSE+100+4)

#define COMMAND_MOUSE_M_CLICK (COMMAND_MOUSE+100+5)

#define COMMAND_MOUSE_SET_ORIGIN_TO_WINDOW (COMMAND_MOUSE+100+6)
#define COMMAND_MOUSE_SET_ORIGIN_TO_IMAGE (COMMAND_MOUSE+100+7)

int MouseLDownAbs(UINT nX, UINT nY);
int MouseLDown(int iScene, CStringArray* saData);
int MouseRDownAbs(UINT nX, UINT nY);
int MouseRDown(int iScene, CStringArray* saData);
int MouseMDownAbs(UINT nX, UINT nY);
int MouseMDown(int iScene, CStringArray* saData);

int MouseLUpAbs(UINT nX, UINT nY);
int MouseLUp(int iScene, CStringArray* saData);
int MouseRUpAbs(UINT nX, UINT nY);
int MouseRUp(int iScene, CStringArray* saData);
int MouseMUpAbs(UINT nX, UINT nY);
int MouseMUp(int iScene, CStringArray* saData);

int MoveMouseAbs(UINT nX, UINT nY);
int MoveMouse(int iScene, CStringArray* saData);

int MoveMouseIncl(int iX, int iY);
int MoveMouseIncl(int iScene, CStringArray* saData);

int MouseVWheel(int iWheel);
int MouseVWheel(int iScene, CStringArray* saData);

int MouseLClick(UINT nX, UINT nY);
int MouseLClick(int iScene, CStringArray* saData);
int MouseRClick(UINT nX, UINT nY);
int MouseRClick(int iScene, CStringArray* saData);
int MouseMClick(UINT nX, UINT nY);
int MouseMClick(int iScene, CStringArray* saData);

extern int g_iClickDulation;
int MoveMouseToImage(int iScene, CStringArray* saData);
int MouseSetOriginToWindow(int iScene, CStringArray* saData);
int MouseSetOriginToImage(int iScene, CStringArray* saData);

void ChangeMouseOrigin(UINT uiX, UINT uiY);