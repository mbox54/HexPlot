// StaticHP.cpp

// \ INFO
// *******************************************************************
// Class for HexPlot Graphical procedure
// include structures and methods for picturing
// based on CStatic
// *******************************************************************

#include "stdafx.h"
#include "StaticHP.h"

// implementation file


// -------------------------------------------------------------------
// class CStaticHP
// -------------------------------------------------------------------
CStaticHP::CStaticHP()
{

	// init
	InitTest();
}


CStaticHP::~CStaticHP()
{
}

// -------------------------------------------------------------------
// Proceed Message Map
// -------------------------------------------------------------------
BEGIN_MESSAGE_MAP(CStaticHP, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// -------------------------------------------------------------------
// Events
// -------------------------------------------------------------------
void CStaticHP::OnPaint()
{
//	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CStatic::OnPaint() for painting messages
					   // Paint on this DC
	
	CPaintDC dcCanvas(this);

	// get DC // not used now
	CDC memdc;
	memdc.CreateCompatibleDC(&dcCanvas);

	// Define Rect range
	CRect rectCanvas;
	this->GetClientRect(&rectCanvas);

	switch (uiPaintMode)
	{
	case 0:

		break;

	case 1:
		// test Draw
		dcCanvas.MoveTo(0, 0);
		dcCanvas.LineTo(100, 100);

		break;

	case 2:
		// test Draw
		dcCanvas.MoveTo(100, 0);
		dcCanvas.LineTo(200, 100);

		break;

	default:
		break;
	}

}


void CStaticHP::InitTest()
{
	// > Test mode
	uiSize = 10;
	uiPaintMode = 0;

}

void CStaticHP::PaintGrid()
{
	uiPaintMode = 1;
	OnPaint();

	Invalidate();
	/*

	// Paint on this DC
	CPaintDC dcCanvas(this);

	// get DC // not used now
	CDC memdc;
	memdc.CreateCompatibleDC(&dcCanvas);

	// Define Rect range
	CRect rectCanvas;
	this->GetClientRect(&rectCanvas);

	// test Draw
	dcCanvas.MoveTo(0, 0);
	dcCanvas.LineTo(100, 100);

	Invalidate();
//	OnPaint();

*/
}

void CStaticHP::PaintGrid2()
{
	uiPaintMode = 2;
	OnPaint();

	Invalidate();

	/*
	// Paint on this DC
	CPaintDC dcCanvas(this);

	// get DC // not used now
	CDC memdc;
	memdc.CreateCompatibleDC(&dcCanvas);

	// Define Rect range
	CRect rectCanvas;
	this->GetClientRect(&rectCanvas);

	// test Draw
	dcCanvas.MoveTo(100, 0);
	dcCanvas.LineTo(200, 100);

	Invalidate();
//	OnPaint();

*/
}



//!debug
//MessageBox(_T("Clicked"));