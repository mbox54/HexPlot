
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

	ON_COMMAND(ID_MAIN_CLICK2, &CHexPlotDlg::OnMainClick2)
END_MESSAGE_MAP()


// Static Global Variables
// Set status bar pane 0 and 1 indicators
static UINT BASED_CODE StatusBarIndicators[] =
{
	ID_INDICATOR_COORDS,
	ID_INDICATOR_STATUS
};


// ===================================================================
// CHexPlotDlg message handlers
// ===================================================================


// -------------------------------------------------------------------
// // Status Bar
// -------------------------------------------------------------------
// Initialize the status bar
// - Create the status bar object
// - Set number of panes to 2
// - Make pane 0 a fixed width
// - Make pane 1 fit the rest of the dialog
// - Draw the status bar
// - Set default status bar text to "" and ""
void CHexPlotDlg::InitStatusBar()
{
	// Create the status bar
	m_statusBar.Create(this);

	// Set number of panes
	m_statusBar.SetIndicators(StatusBarIndicators, sizeof(StatusBarIndicators) / sizeof(StatusBarIndicators[0]));

	// Make the device pane a fixed width
	m_statusBar.SetPaneInfo(0, ID_INDICATOR_COORDS, SBPS_NORMAL, 100);

	// Make the status pane fit the rest of the status bar
	m_statusBar.SetPaneInfo(1, ID_INDICATOR_STATUS, SBPS_STRETCH, 0);

	// Draw the status bar
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, ID_INDICATOR_STATUS);

	SetStatusText0(_T(""));
	SetStatusText1(_T(""));
}

// Set status bar text for specified pane 0
void CHexPlotDlg::SetStatusText0(const CString & text)
{
	// Set the status bar text
	m_statusBar.SetPaneText(0, text);
}

// Set status bar text for specified pane 1
void CHexPlotDlg::SetStatusText1(const CString & text)
{
	// Set the status bar text
	m_statusBar.SetPaneText(1, text);
}

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

	// init Status bar
	InitStatusBar();

	// init Canvas controls
	// NOTE: !can be implemented only after creation Canvas instance.
	m_GridHP.SetCanvas(&this->m_Canvas);
	this->m_Canvas.SetCanvasRect();
	
	
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
//		CPaintDC dcCanvas(&m_Canvas);

		// get DC
//		CDC memdcLogo;
//		memdcLogo.CreateCompatibleDC(&dcCanvas);

		// Define Rect range
//		CRect rectCanvas;
//		m_Canvas.GetClientRect(&rectCanvas);

		// test Draw
//		dcCanvas.MoveTo(0, 0);
//		dcCanvas.LineTo(100, 100);

//		m_Canvas.PaintGrid();


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
	// > init vars
	// HexPlot Grid

	//m_Canvas.PaintGrid();
//	m_GridHP.AddNode(POINT Pos);

	// proceed this Dialog Paint Message
//	CDialogEx::OnPaint();

	//!debug
	//MessageBox(_T("Clicked"));

	this->m_GridHP.PaintGrid();

}


void CHexPlotDlg::OnMainClick2()
{
	// > init vars
	// HexPlot Grid
	m_Canvas.PaintGrid2();

	// proceed this Dialog Paint Message
//	CDialogEx::OnPaint();

	//!debug
	//MessageBox(_T("Clicked"));

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
			POINT aPoint = m_Canvas.GetCursorCoords();

			CString str_Coord;

			// construct coord string
			str_Coord.Format(L"%03d %s %03d", aPoint.x, "; ", aPoint.y);

			// output in Status bar
			SetStatusText0(str_Coord);

			/* //!debug
			MessageBox(_T("Clicked"));
			MessageBeep(MB_OK);
			*/
		}
	}


	// return to main event Proc
	return CDialogEx::OnSetCursor(pWnd, nHitTest, message);
}

