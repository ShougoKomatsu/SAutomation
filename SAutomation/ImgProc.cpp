#include "stdafx.h"


void test(HWND dlg)
{ // ���j�^�[�T�C�Y�擾
  HWND desktop = GetDesktopWindow();
  RECT rect;
  GetWindowRect(desktop, &rect);


  // DIB�̏���ݒ肷��
  BITMAPINFO bmpInfo;
  bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  bmpInfo.bmiHeader.biWidth = rect.right;
  bmpInfo.bmiHeader.biHeight = -rect.bottom;
  bmpInfo.bmiHeader.biPlanes = 1;
  bmpInfo.bmiHeader.biBitCount = 24; //cv::Mat�̉摜���A���t�@�`�����l���L��ɂ���ꍇ�͂�32;
  bmpInfo.bmiHeader.biCompression = BI_RGB;


  LPDWORD lpPixel;
  HDC hDC = GetDC(desktop);
  HBITMAP hBitmap = CreateDIBSection(hDC, &bmpInfo, DIB_RGB_COLORS, (void**)&lpPixel, NULL, 0);
  HDC hMemDC = CreateCompatibleDC(hDC);
  SelectObject(hMemDC, hBitmap);

  BYTE* byData;
  byData = new BYTE[3000*4000*3];
    //hDC�̉摜�i�X�N���[���V���b�g�j��hMemDC�ɃR�s�[����
    BitBlt(hMemDC, 0, 0, rect.right, rect.bottom, hDC, 0, 0, SRCCOPY);
    // hMemDC�̓��e��cv::Mat�̉摜�imonitor_img�j�ɃR�s�[
    GetDIBits(hMemDC, hBitmap, 0, rect.bottom, byData, (BITMAPINFO *)&bmpInfo, DIB_RGB_COLORS);  //copy from hwindowCompatibleDC to hbwindow
	delete byData;
  //�������J��
  ReleaseDC(desktop, hDC);
  DeleteDC(hMemDC);
  DeleteObject(hBitmap);

  return ;
}