#pragma once
#include "stdafx.h"


#include "Automation.h"

#define COMMAND_MOUSE_MOVE (COMMAND_MOUSE+MOUSEEVENTF_MOVE)
#define COMMAND_MOUSE_L_DOWN (COMMAND_MOUSE+MOUSEEVENTF_LEFTDOWN)
#define COMMAND_MOUSE_L_UP (COMMAND_MOUSE+MOUSEEVENTF_LEFTUP)

#define COMMAND_MOUSE_R_DOWN (COMMAND_MOUSE+MOUSEEVENTF_RIGHTDOWN)
#define COMMAND_MOUSE_R_UP (COMMAND_MOUSE+MOUSEEVENTF_RIGHTUP)

#define COMMAND_WHEEL (COMMAND_MOUSE+MOUSEEVENTF_WHEEL)

#define COMMAND_MOUSE_L_CLICK (COMMAND_MOUSE+100+MOUSEEVENTF_LEFTDOWN)
#define COMMAND_MOUSE_R_CLICK (COMMAND_MOUSE+100+MOUSEEVENTF_RIGHTDOWN)


int MouseLDown(UINT nX, UINT nY);
int MouseLDown(CStringArray* saData);
int MouseRDown(UINT nX, UINT nY);
int MouseRDown(CStringArray* saData);

int MouseLUp(UINT nX, UINT nY);
int MouseLUp(CStringArray* saData);
int MouseRUp(UINT nX, UINT nY);
int MouseRUp(CStringArray* saData);

int MoveMouse(UINT nX, UINT nY);
int MoveMouse(CStringArray* saData);
int MouseVWheel(int iWheel);
int MouseVWheel(CStringArray* saData);

int MouseLClick(UINT nX, UINT nY);
int MouseLClick(CStringArray* saData);
int MouseRClick(UINT nX, UINT nY);
int MouseRClick(CStringArray* saData);

extern int g_iClickDulation;