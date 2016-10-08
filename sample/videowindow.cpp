#include "stdafx.h"
#include "videowindow.h"


videowindow::videowindow()
{
  registerclass();
}


videowindow::~videowindow()
{
}


BOOL videowindow::registerclass()
{
  WNDCLASS wc;
  wc.style = 0;
  wc.lpfnWndProc = ::DefWindowProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = (HINSTANCE)::GetModuleHandle(NULL);
  wc.hIcon = NULL;
  wc.hCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
  wc.hbrBackground = (HBRUSH)(COLOR_3DFACE + 1);
  wc.lpszMenuName = NULL;
  wc.lpszClassName = VIDEOWINDOW_CLASSNAME;
  return AfxRegisterClass(&wc);
}
