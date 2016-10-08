#pragma once
#include "afxwin.h"
#define VIDEOWINDOW_CLASSNAME    _T("videowindow")  // Window class name
class videowindow :
  public CWnd
{
public:
  videowindow();
  virtual ~videowindow();
private:
  BOOL registerclass();
};

