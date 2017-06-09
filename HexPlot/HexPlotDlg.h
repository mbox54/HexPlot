
// HexPlotDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "HexAlgorithm.h"
#include "StaticHP.h"
#include "GridHP.h"

// -------------------------------------------------------------------
// CHexPlotDlg dialog
// -------------------------------------------------------------------
class CHexPlotDlg : public CDialogEx
{
// Construction
public:
	CHexPlotDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HEXPLOT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:

	// > Properties
	// System
	HICON m_hIcon;

	// // Menu main
	CMenu m_MenuMain;

	// // Status bar
	CStatusBar	m_statusBar;

	// HP Main / Additional
	// // Picture field
	CStaticHP m_Canvas;

	// // Hex Plot Object
	CGridHP m_GridHP; 


// Procs
	// Status Bar
	void InitStatusBar();

	// Set the status bar text
	void SetStatusText0(const CString& text);
	void SetStatusText1(const CString& text);


	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnMainExit();
	afx_msg void OnMainClick();

	// For Canvas. Intercepters
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMainClick2();
};
