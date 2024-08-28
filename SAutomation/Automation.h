#include "stdafx.h"	
#include "Common.h"
#include "Perser.h"
#ifndef AUTOMATION_DEFINE
#define AUTOMATION_DEFINE

#define COMMAND_UNDEFINED (0)
#define COMMAND_COMMON (0)
#define COMMAND_MOUSE (1000)
#define COMMAND_IMGPROC (2000)
#define COMMAND_FLOW (3000)
#define COMMAND_VARIABLE (4000)

#define COMMAND_DELAY (COMMAND_COMMON + 1)
//#define COMMAND_BREAK (COMMAND_COMMON + 2)
#define COMMAND_KEY_DOWN_UP (COMMAND_COMMON +3)
#define COMMAND_KEY_DOWN (COMMAND_COMMON +4)
#define COMMAND_KEY_UP (COMMAND_COMMON +5)
#define COMMAND_REPEAT (COMMAND_COMMON +6)
#define COMMAND_REPEAT_END (COMMAND_COMMON +7)
#define COMMAND_NOTING (COMMAND_COMMON +8)
#define COMMAND_DECRARE (COMMAND_COMMON + 9)
#define COMMAND_WAIT (COMMAND_COMMON + 10)
#define COMMAND_MAXIMIZE (COMMAND_COMMON + 11)
#define COMMAND_MINIMIZE (COMMAND_COMMON + 12)
#define COMMAND_WINDOW_FORWARD (COMMAND_COMMON + 13)
#define COMMAND_WINDOW_SIZE (COMMAND_COMMON + 14)
#define COMMAND_WINDOW_POS (COMMAND_COMMON + 15)
#define COMMAND_RUN (COMMAND_COMMON + 16)
#define COMMAND_INPUT (COMMAND_COMMON + 17)
#define COMMAND_WAIT_KEY (COMMAND_COMMON + 18)
#define COMMAND_MESSAGEBOX (COMMAND_COMMON + 19)

#define COMMAND_EXIT (COMMAND_FLOW +1)
#define COMMAND_LABEL (COMMAND_FLOW +2)
#define COMMAND_ERROR_TREAT (COMMAND_FLOW+3)
#define COMMAND_GOTO (COMMAND_FLOW+4)
#define COMMAND_SWITCH_BY_INPUT (COMMAND_FLOW+5)
#define COMMAND_SUB (COMMAND_FLOW +6)
#define COMMAND_CALL_SUB (COMMAND_FLOW +7)
#define COMMAND_END_SUB (COMMAND_FLOW +8)

#define COMMAND_WAIT_IMG (COMMAND_IMGPROC + 1)
#define COMMAND_WAIT_UPDATE (COMMAND_IMGPROC + 2)
#define COMMAND_SCREENSHOT (COMMAND_IMGPROC + 3)
#define COMMAND_WRITE_IMAGE (COMMAND_IMGPROC + 4)

#define COMMAND_VARIABLE_INT (COMMAND_VARIABLE+1)
#define COMMAND_AREEQUAL_INT (COMMAND_VARIABLE+2)
#define COMMAND_VARIABLE_STR (COMMAND_VARIABLE+3)
#define COMMAND_VARIABLE_IMG (COMMAND_VARIABLE+4)
#define COMMAND_VARIABLE_POINT (COMMAND_VARIABLE+5)


ReturnValue OperateCommand(int* iSceneData, LPVOID Halt, LPVOID Suspend, LONGLONG* Special1, CString sDataLine, CString* sReturnParam);




ReturnValue GetKeyCode(CString sData, BOOL* bUnicode, TCHAR* tch, BYTE* byData);
ReturnValue Input(CString sInputWithDblQuart);

#endif