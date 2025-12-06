#pragma once


#include "common.h"

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
#define COMMAND_MOUSE_L_CLICK_IMG (COMMAND_MOUSE+100+9)

#define COMMAND_MOUSE_L_REPEATCLICK (COMMAND_MOUSE+100+10)
#define COMMAND_MOUSE_R_REPEATCLICK (COMMAND_MOUSE+100+11)
#define COMMAND_MOUSE_M_REPEATCLICK (COMMAND_MOUSE+100+12)

#define COMMAND_MOUSE_L_DRAG_AND_DROP (COMMAND_MOUSE+100+13)

ReturnValue MouseLDownAbs(UINT nX, UINT nY);
ReturnValue MouseLDown(CString sDir, int iScene, CStringArray* saData);
ReturnValue MouseRDownAbs(UINT nX, UINT nY);
ReturnValue MouseRDown(CString sDir, int iScene, CStringArray* saData);
ReturnValue MouseMDownAbs(UINT nX, UINT nY);
ReturnValue MouseMDown(CString sDir, int iScene, CStringArray* saData);

ReturnValue MouseLUpAbs(UINT nX, UINT nY);
ReturnValue MouseLUp(CString sDir, int iScene, CStringArray* saData);
ReturnValue MouseRUpAbs(UINT nX, UINT nY);
ReturnValue MouseRUp(CString sDir, int iScene, CStringArray* saData);
ReturnValue MouseMUpAbs(UINT nX, UINT nY);
ReturnValue MouseMUp(CString sDir, int iScene, CStringArray* saData);

ReturnValue MoveMouseAbs(UINT nX, UINT nY);
ReturnValue MoveMouse(CString sDir, int iScene, CStringArray* saData);

ReturnValue MoveMouseIncl(int iX, int iY);
ReturnValue MoveMouseIncl(CString sDir, int iScene, CStringArray* saData);

ReturnValue MouseVWheel(int iWheel);
ReturnValue MouseVWheel(CString sDir, int iScene, CStringArray* saData);

ReturnValue MouseLClick(UINT nX, UINT nY, int iClickDulation);
ReturnValue MouseLClick(CString sDir, int iScene, CStringArray* saData);
ReturnValue MouseRClick(UINT nX, UINT nY, int iClickDulation);
ReturnValue MouseRClick(CString sDir, int iScene, CStringArray* saData);
ReturnValue MouseMClick(UINT nX, UINT nY, int iClickDulation);
ReturnValue MouseMClick(CString sDir, int iScene, CStringArray* saData);

ReturnValue MouseLRepeatClick(CString sDir, int iScene, CStringArray* saData,LPVOID Halt, LPVOID Suspend);

ReturnValue MoveMouseToItem(CString sDir, int iScene, CStringArray* saData);
ReturnValue MoveMouseToImage(CString sDir, int iScene, CStringArray* saData);
ReturnValue MouseSetOriginToWindow(CString sDir, int iScene, CStringArray* saData);
ReturnValue MouseSetOriginToImage(CString sDir, int iScene, CStringArray* saData);

ReturnValue MouseLClickImage(CString sDir, int iScene, CStringArray* saData);

ReturnValue MouseLDragAndDrop(CString sDir, int iScene, CStringArray* saData);

void ChangeMouseOrigin(UINT uiX, UINT uiY);