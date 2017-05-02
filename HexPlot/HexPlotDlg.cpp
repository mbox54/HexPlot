
// HexPlotDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HexPlot.h"
#include "HexPlotDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// -------------------------------------------------------------------
// CAboutDlg dialog used for App About
// -------------------------------------------------------------------
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



// -------------------------------------------------------------------
// CHexPlotDlg dialog
// -------------------------------------------------------------------

CHexPlotDlg::CHexPlotDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_HEXPLOT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHexPlotDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_CANVAS, m_Canvas);
}

BEGIN_MESSAGE_MAP(CHexPlotDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_MAIN_EXIT, &CHexPlotDlg::OnMainExit)
	ON_COMMAND(ID_MAIN_CLICK, &CHexPlotDlg::OnMainClick)

	// intercept for Canvas
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()


// CHexPlotDlg message handlers

BOOL CHexPlotDlg::OnInitDialog()
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

	// ---------------------------------------------
	// TODO: Add extra initialization here
	// ---------------------------------------------

	// init Menu
	m_MenuMain.LoadMenu(IDR_MENU_SYSTEM);
	SetMenu(&m_MenuMain);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CHexPlotDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CHexPlotDlg::OnPaint()
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

		// Paint on DC
		CPaintDC dcCanvas(&m_Canvas);

		// get DC
		CDC memdcLogo;
		memdcLogo.CreateCompatibleDC(&dcCanvas);

		// Define Rect range
		CRect rectCanvas;
		m_Canvas.GetClientRect(&rectCanvas);

		// test Draw
		dcCanvas.MoveTo(0, 0);
		dcCanvas.LineTo(100, 100);

		// return to Common event Proc
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CHexPlotDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CHexPlotDlg::OnMainExit()
{

	this->OnOK();	
}


void CHexPlotDlg::OnMainClick()
{

	MessageBox(_T("Clicked"));
}


BOOL CHexPlotDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: Add your message handler code here and/or call default

	// Mouse Move Event
	if (message == WM_MOUSEMOVE)
	{
		// Canvas Object
		if (pWnd->m_hWnd == ::GetDlgItem(m_hWnd, IDC_STATIC_CANVAS))
		{
			MessageBox(_T("Clicked"));
			MessageBeep(MB_OK);
		}
	}


	// return to main event Proc
	return CDialogEx::OnSetCursor(pWnd, nHitTest, message);
}
