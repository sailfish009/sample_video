
// sampleDlg.h : header file
//

#pragma once
#include "videowindow.h"

// yuv and sdl
#if false
#include "../include/SDL.h"
#include "../include/SDL_thread.h"
#include "../include/SDL_syswm.h"
#pragma comment(lib, "../lib/SDL2.lib")
#endif

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "version.lib")
#pragma comment(lib, "imm32.lib")


// std::unique_ptr
#include <memory>

// opencv v4.0
#if true 
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/highgui/highgui_c.h>

#pragma comment(lib, "opencv_core401d.lib" )
#pragma comment(lib, "opencv_imgproc401d.lib" )
#pragma comment(lib, "opencv_highgui401d.lib" )
#pragma comment(lib, "opencv_ml401d.lib" )
#pragma comment(lib, "opencv_video401d.lib" )
#pragma comment(lib, "opencv_features2d401d.lib" )
#pragma comment(lib, "opencv_calib3d401d.lib" )
#pragma comment(lib, "opencv_imgcodecs401d.lib" )
#pragma comment(lib, "opencv_videoio401d.lib" )

using namespace cv;
#endif

// CsampleDlg dialog
class CsampleDlg : public CDialogEx
{
// Construction
public:
	CsampleDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SAMPLE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
  afx_msg void OnBnClickedOk();
  afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()

public:
  static videowindow m_vw;

private:

  // yuv and sdl
#if false
  FILE * fp;
  std::unique_ptr<UINT8[]> yPlane;
  std::unique_ptr<UINT8[]> uPlane;
  std::unique_ptr<UINT8[]> vPlane;
  size_t yPlaneSz, uvPlaneSz;
  int pixel_w;
  int pixel_h;
  int screen_w;
  int screen_h;
  int frame_w;
  int frame_h;
  int uvPitch;
  BOOL b_start;
  SDL_Event event;
  SDL_Renderer *renderer;
  SDL_Window *screen;
  SDL_SysWMinfo info;
  SDL_Texture *texture;
  SDL_Rect rect;
  SDL_Rect win_rect;
  void init_sdl(UINT16 width, UINT16 height);
  void display_proc(BOOL *b_start);
#endif

  // opencv v4.0
#if true
  void init_image();
#endif

  RECT m_rect;

};
