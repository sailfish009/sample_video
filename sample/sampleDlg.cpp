//========================================================================
//
// Copyright (c) 2019 Ji Wong Park <sailfish009@gmail.com>
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would
//    be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not
//    be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source
//    distribution.
//
//========================================================================

// sampleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "sample.h"
#include "sampleDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

videowindow CsampleDlg::m_vw;

// yuv and sdl
#if false
#include <thread>
#include <mutex>
std::mutex g_mutex;
std::condition_variable g_cond;
#endif

// opencv v4.0
#if true 
Mat image;
Mat img;
Mat binary;
Mat grayscale;
#endif

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CsampleDlg dialog



CsampleDlg::CsampleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SAMPLE_DIALOG, pParent)
  // yuv and sdl
#if false
  ,
  fp(nullptr),
  screen_w(1920), screen_h(1080),
  pixel_w(1920), pixel_h(1080),
  yPlane(nullptr), uPlane(nullptr), vPlane(nullptr),
  b_start(false)
#endif
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CsampleDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialogEx::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_CUSTOM1, m_vw);
}

BEGIN_MESSAGE_MAP(CsampleDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
  ON_BN_CLICKED(IDOK, &CsampleDlg::OnBnClickedOk)
  ON_WM_CLOSE()
END_MESSAGE_MAP()


// CsampleDlg message handlers

BOOL CsampleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

  // yuv and sdl
#if false 
  fopen_s(&fp, "../../1.yuv", "rb+");

  yPlaneSz = pixel_w * pixel_h;
  uvPlaneSz = pixel_w * pixel_h / 4;
  uvPitch = pixel_w / 2;
  yPlane = std::make_unique<UINT8[]>(yPlaneSz);
  uPlane = std::make_unique<UINT8[]>(uvPlaneSz);
  vPlane = std::make_unique<UINT8[]>(uvPlaneSz);
  init_sdl(1920, 1080);
#endif

  init_image();

 	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CsampleDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CsampleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CsampleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

  // opencv v4.0
#if true
void CsampleDlg::init_image()
{
  m_vw.GetClientRect(&m_rect);

  image = cv::imread("../../1.png");
  if (image.data == 0) { MessageBox(L"Image File Open Error", L"Error"); return; }

  Rect r
  (
    (int)m_rect.left, 
    (int)m_rect.top, 
    (int)(m_rect.right - m_rect.left), 
    (int)(m_rect.bottom - m_rect.top)
  );

  resize(image, img, Size(r.width, r.height), 0, 0, INTER_CUBIC);
  cvtColor(img, grayscale, COLOR_BGR2GRAY);

  imshow("Display window", img);
  HWND hwnd = (HWND)cvGetWindowHandle("Display window");
  HWND hParent = ::GetParent(hwnd);
  ::SetParent(hwnd, m_vw.m_hWnd);
  ::ShowWindow(hParent, SW_HIDE);

  std::vector<std::vector<Point> > contours;
  std::vector<Vec4i> hierarchy;
  threshold(grayscale, binary, 127, 255, 0);

  findContours(binary, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	
  Mat drawing = img;

#if true 
  double epsilon = 1;
  std::vector<Point> vertex;
  if (contours.size() > 0 && hierarchy.size() > 0)
  {
    approxPolyDP(Mat(contours[0]), vertex, epsilon, true);
    if (vertex.size() >= 4)
    {
      std::vector<int> vec_x;
      std::vector<int> vec_y;
      for (size_t i = 0; i < vertex.size(); ++i)
      {
        vec_x.push_back(vertex[i].x);
        vec_y.push_back(vertex[i].y);
      }
      double min_x = *std::min_element(vec_x.begin(), vec_x.end());
      double max_x = *std::max_element(vec_x.begin(), vec_x.end());
      double min_y = *std::min_element(vec_y.begin(), vec_y.end());
      double max_y = *std::max_element(vec_y.begin(), vec_y.end());

      Point p1 = Point(min_x, min_y);
      Point p2 = Point(max_x, max_y);

      rectangle(drawing, p1, p2, Scalar(0, 0, 255));
    }
  }
#endif

#if false 
  for(int i=0; i< contours.size(); ++i)
  {
    Scalar color = Scalar(0, 0, 255);
    drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
  }
#endif

  namedWindow("Contours", WINDOW_AUTOSIZE);
  imshow("Contours", drawing);
	
}
#endif


// yuv and sdl
#if false
void CsampleDlg::init_sdl(UINT16 width, UINT16 height)
{
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
    exit(1);
  }

  // Make a screen to put our video
  screen = SDL_CreateWindowFrom(m_vw.m_hWnd);
  if (!screen) {
    exit(1);
  }

  renderer = SDL_CreateRenderer(screen, -1, 0);
  if (!renderer) {
    exit(1);
  }

  texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_YV12,
    SDL_TEXTUREACCESS_STREAMING, screen_w, screen_h);

  {
    std::lock_guard<std::mutex> lock(g_mutex);
    pixel_w = width;
  }
  pixel_h = height;

  m_vw.GetClientRect(&m_rect);
  frame_w = m_rect.right - m_rect.left;
  frame_h = m_rect.bottom - m_rect.top;

  rect.x = 0;
  rect.y = 0;
  rect.w = pixel_w;
  rect.h = pixel_h;

  win_rect.x = m_rect.left;
  win_rect.y = m_rect.top;
  win_rect.w = frame_w;
  win_rect.h = frame_h;

  uvPitch = pixel_w / 2;
}
#endif

void CsampleDlg::OnBnClickedOk()
{
  m_vw.GetClientRect(&m_rect);
// yuv and sdl
#if false
  switch (b_start)
  {
  case true:
  {
    {
      std::lock_guard<std::mutex> lock(g_mutex);
      b_start = FALSE;
    }
    g_cond.notify_one();
    fseek(fp, 0, SEEK_SET);
    GetDlgItem(IDOK)->SetWindowTextW(L"Start");
  }
  break;

  case false:
  {
    b_start = TRUE;
    std::thread t = std::thread([=] {display_proc(&b_start); });
    t.detach();
    GetDlgItem(IDOK)->SetWindowTextW(L"Stop");
  }
  break;
  }
#endif
}


// yuv and sdl
#if false
void CsampleDlg::display_proc(BOOL *b_start)
{
  std::unique_lock<std::mutex> lock(g_mutex);
  while (*b_start)
  {
    size_t st = fread(yPlane.get(), 1, pixel_w * pixel_h, fp);
    fread(uPlane.get(), 1, pixel_w * pixel_h / 4, fp);
    fread(vPlane.get(), 1, pixel_w * pixel_h / 4, fp);

    SDL_UpdateYUVTexture(texture, NULL, yPlane.get(), pixel_w, uPlane.get(),
      uvPitch, vPlane.get(), uvPitch);
    SDL_RenderCopy(renderer, texture, &rect, &win_rect);
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
    if (st == 0)
      fseek(fp, 0, SEEK_SET);

    g_cond.wait_for(lock, std::chrono::milliseconds(33));
  }
}
#endif



void CsampleDlg::OnClose()
{
  // yuv and sdl
#if false
  if (fp != nullptr) fclose(fp);
#endif

  CDialogEx::OnClose();
}
