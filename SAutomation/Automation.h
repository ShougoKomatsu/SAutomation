#include "stdafx.h"
#include "Perser.h"	

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

#define COMMAND_VARIABLE_INT (COMMAND_VARIABLE+1)
#define COMMAND_ISEQUAL_INT (COMMAND_VARIABLE+2)
#define COMMAND_ADD_INT (COMMAND_VARIABLE+3)
#define COMMAND_SUB_INT (COMMAND_VARIABLE+4)
#define COMMAND_MULT_INT (COMMAND_VARIABLE+5)
#define COMMAND_DIV_INT (COMMAND_VARIABLE+6)

int OperateCommand(int* iSceneData, LPVOID Halt, LPVOID Suspend, LONGLONG* Special1, CString sDataLine, CString* sReturnParam);

extern CString g_sDir;

#define RETURN_NORMAL (0)
#define RETURN_FAILED (-1)
#define RETURN_END (10)
#define RETURN_HALT (-2)
#define RETURN_ERROR_TREAT (11)
#define RETURN_IF (100)
#define RETURN_LABEL (101)
#define RETURN_GOTO (102)
#define RETURN_GOTO_BY_SWITCH (103)
#define RETURN_CALL_SUB (104)
#define RETURN_END_SUB (105)
#define RETURN_SUB (106)

#define ERROR_TREAT_UNDEFINED (-1)
#define ERROR_TREAT_END (0)
#define ERROR_TREAT_RESUME (1)
#define ERROR_TREAT_GOTO (2)

int GetKeyCode(CString sData, BOOL* bUnicode, TCHAR* tch, BYTE* byData);
BOOL Input(CString sInputWithDblQuart);