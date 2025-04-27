#pragma once

#include "stdafx.h"
#include "common.h"



BOOL GetOperandCameraSrc(CString sDataLine, int* iCommandType);
BOOL GetOperandImgSrc(CString sDataLine, int* iCommandType);
ImgRGB* GetImgValuePointer(int iScene, CString sArg);
const ImgRGB* GetImgValuePointerConst(int iScene, CString sArg);
ReturnValue SetCameraValue(Camera* cameraDst, int iScene, CString sData);
ReturnValue SetImgValue(ImgRGB* imgRGBDst, int iScene, CString sData);
Camera* GetCameraPointer(int iScene, CString sArg);