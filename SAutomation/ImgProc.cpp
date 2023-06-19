#include "stdafx.h"


void test(HWND dlg)
{ // モニターサイズ取得
  HWND desktop = GetDesktopWindow();
  RECT rect;
  GetWindowRect(desktop, &rect);


  // DIBの情報を設定する
  BITMAPINFO bmpInfo;
  bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  bmpInfo.bmiHeader.biWidth = rect.right;
  bmpInfo.bmiHeader.biHeight = -rect.bottom;
  bmpInfo.bmiHeader.biPlanes = 1;
  bmpInfo.bmiHeader.biBitCount = 24; //cv::Matの画像をアルファチャンネル有りにする場合はは32;
  bmpInfo.bmiHeader.biCompression = BI_RGB;


  LPDWORD lpPixel;
  HDC hDC = GetDC(desktop);
  HBITMAP hBitmap = CreateDIBSection(hDC, &bmpInfo, DIB_RGB_COLORS, (void**)&lpPixel, NULL, 0);
  HDC hMemDC = CreateCompatibleDC(hDC);
  SelectObject(hMemDC, hBitmap);

  BYTE* byData;
  byData = new BYTE[3000*4000*3];
    //hDCの画像（スクリーンショット）をhMemDCにコピーする
    BitBlt(hMemDC, 0, 0, rect.right, rect.bottom, hDC, 0, 0, SRCCOPY);
    // hMemDCの内容をcv::Matの画像（monitor_img）にコピー
    GetDIBits(hMemDC, hBitmap, 0, rect.bottom, byData, (BITMAPINFO *)&bmpInfo, DIB_RGB_COLORS);  //copy from hwindowCompatibleDC to hbwindow
	delete byData;
  //メモリ開放
  ReleaseDC(desktop, hDC);
  DeleteDC(hMemDC);
  DeleteObject(hBitmap);

  return ;
}