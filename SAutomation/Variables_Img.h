#pragma once

#include "stdafx.h"
#include "common.h"



BOOL GetOperandCameraSrc(CString sDataLine, int* iCommandType);
BOOL GetOperandImgSrc(CString sDataLine, int* iCommandType);
ImgRGB* GetImgValuePointer(CString sDir, int iScene, CString sArg);
const ImgRGB* GetImgValuePointerConst(CString sDir, int iScene, CString sArg);
ReturnValue SetCameraValue(CString sDir, int iScene, Camera* cameraDst, CString sData);
ReturnValue SetImgValue(CString sDir, int iScene, ImgRGB* imgRGBDst, CString sData);
Camera* GetCameraPointer(CString sDir, int iScene, CString sArg);