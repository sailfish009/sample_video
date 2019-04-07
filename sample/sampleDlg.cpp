
// sampleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "sample.h"
#include "sampleDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <thread>
#include <mutex>
std::mutex g_mutex;
std::condition_variable g_cond;
videowindow CsampleDlg::m_vw;

#if false
Mat image;
Mat img;
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
	: CDialogEx(IDD_SAMPLE_DIALOG, pParent),
  fp(nullptr),
  screen_w(1920), screen_h(1080),
  pixel_w(1920), pixel_h(1080),
  yPlane(nullptr), uPlane(nullptr), vPlane(nullptr),
  b_start(false)
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
#if true
  fopen_s(&fp, "../../1.yuv", "rb+");

  yPlaneSz = pixel_w * pixel_h;
  uvPlaneSz = pixel_w * pixel_h / 4;
  uvPitch = pixel_w / 2;
  yPlane = std::make_unique<UINT8[]>(yPlaneSz);
  uPlane = std::make_unique<UINT8[]>(uvPlaneSz);
  vPlane = std::make_unique<UINT8[]>(uvPlaneSz);
  init_sdl(1920, 1080);
#endif

  // opencv v4.0
#if false
  HWND img_hwnd = GetDlgItem(IDC_IMAGE)->m_hWnd;
  RECT rect;
  ::GetClientRect(img_hwnd, &rect);

  image = cv::imread("./1.png");
  if (image.data == 0){ MessageBox(L"Image File Open Error", L"Error");}

  Rect r
  (
    (int)rect.left, 
    (int)rect.top, 
    (int)(rect.right - rect.left), 
    (int)(rect.bottom - rect.top)
  );

  resize(image, img, Size(r.width, r.height), 0, 0, INTER_CUBIC);

  imshow("Display window", img);
  HWND hwnd = (HWND)cvGetWindowHandle("Display window");
  HWND hParent = ::GetParent(hwnd);
  ::SetParent(hwnd, img_hwnd);
  ::ShowWindow(hParent, SW_HIDE);
	
  std::vector<Vec4i> hierarchy;
  threshold(gray, bin, 127, 255, 0);
  findcontours(bin, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	
  Mat drawing = img;
  for(int i=0; i< contours.size(); ++i)
  {
    scalar color = scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
    drawcontours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
  }
  namedWindow("Contours", WINDOW_AUTOSIZE);
  imshow("Contours", drawing);
	
#endif

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

void CsampleDlg::OnBnClickedOk()
{
  m_vw.GetClientRect(&m_rect);
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
}


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



void CsampleDlg::OnClose()
{
  if (fp != nullptr)
    fclose(fp);

  CDialogEx::OnClose();
}
