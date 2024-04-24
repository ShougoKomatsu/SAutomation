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

#define COMMAND_MOUSE_SET_ORIGIN (COMMAND_MOUSE+100+6)

int MouseLDown(UINT nX, UINT nY);
int MouseLDown(CStringArray* saData);
int MouseRDown(UINT nX, UINT nY);
int MouseRDown(CStringArray* saData);
int MouseMDown(UINT nX, UINT nY);
int MouseMDown(CStringArray* saData);

int MouseLUp(UINT nX, UINT nY);
int MouseLUp(CStringArray* saData);
int MouseRUp(UINT nX, UINT nY);
int MouseRUp(CStringArray* saData);
int MouseMUp(UINT nX, UINT nY);
int MouseMUp(CStringArray* saData);

int MoveMouse(UINT nX, UINT nY);
int MoveMouse(CStringArray* saData);

int MoveMouseIncl(int iX, int iY);
int MoveMouseIncl(CStringArray* saData);

int MouseVWheel(int iWheel);
int MouseVWheel(CStringArray* saData);

int MouseLClick(UINT nX, UINT nY);
int MouseLClick(CStringArray* saData);
int MouseRClick(UINT nX, UINT nY);
int MouseRClick(CStringArray* saData);
int MouseMClick(UINT nX, UINT nY);
int MouseMClick(CStringArray* saData);

extern int g_iClickDulation;
int MoveMouseToImage(CStringArray* saData);
int MouseSetOrigin(CStringArray* saData);