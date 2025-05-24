#pragma once

#include "stdafx.h"
#include "Common.h"

#include "SImgProc_ex.h"
#pragma comment(lib, "simgproc.lib")

ReturnValue Flow_WriteImage(CString sDir, int iScene, CStringArray* saData);