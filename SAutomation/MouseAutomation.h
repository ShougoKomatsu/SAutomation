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
#define COMMAND_MOUSE_MOVE_TO_ITEM (COMMAND_MOUSE+100+8)

ReturnValue MouseLDownAbs(UINT nX, UINT nY);
ReturnValue MouseLDown(int iScene, CStringArray* saData);
ReturnValue MouseRDownAbs(UINT nX, UINT nY);
ReturnValue MouseRDown(int iScene, CStringArray* saData);
ReturnValue MouseMDownAbs(UINT nX, UINT nY);
ReturnValue MouseMDown(int iScene, CStringArray* saData);

ReturnValue MouseLUpAbs(UINT nX, UINT nY);
ReturnValue MouseLUp(int iScene, CStringArray* saData);
ReturnValue MouseRUpAbs(UINT nX, UINT nY);
ReturnValue MouseRUp(int iScene, CStringArray* saData);
ReturnValue MouseMUpAbs(UINT nX, UINT nY);
ReturnValue MouseMUp(int iScene, CStringArray* saData);

ReturnValue MoveMouseAbs(UINT nX, UINT nY);
ReturnValue MoveMouse(int iScene, CStringArray* saData);

ReturnValue MoveMouseIncl(int iX, int iY);
ReturnValue MoveMouseIncl(int iScene, CStringArray* saData);

ReturnValue MouseVWheel(int iWheel);
ReturnValue MouseVWheel(int iScene, CStringArray* saData);

ReturnValue MouseLClick(UINT nX, UINT nY);
ReturnValue MouseLClick(int iScene, CStringArray* saData);
ReturnValue MouseRClick(UINT nX, UINT nY);
ReturnValue MouseRClick(int iScene, CStringArray* saData);
ReturnValue MouseMClick(UINT nX, UINT nY);
ReturnValue MouseMClick(int iScene, CStringArray* saData);

ReturnValue MoveMouseToItem(int iScene, CStringArray* saData);
ReturnValue MoveMouseToImage(int iScene, CStringArray* saData);
ReturnValue MouseSetOriginToWindow(int iScene, CStringArray* saData);
ReturnValue MouseSetOriginToImage(int iScene, CStringArray* saData);

void ChangeMouseOrigin(UINT uiX, UINT uiY);