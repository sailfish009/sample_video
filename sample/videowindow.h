#pragma once
#include "afxwin.h"
#define VIDEOWINDOW_CLASSNAME    L"videowindow"  // Window class name
class videowindow :
  public CWnd
{
public:
  videowindow();
  virtual ~videowindow();
private:
  BOOL registerclass();
};

