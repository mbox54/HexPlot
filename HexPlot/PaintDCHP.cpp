// PaintDCHP.h

// \ INFO
// *******************************************************************
// Class for PaintDC HexPlot Graphics
// include additional procedures for HexPlot graphics
// based on CPaintDC
// *******************************************************************

// implementation file

//////////////////////////////////////////////////////////////////////
// Includes
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PaintDCHP.h"


// -------------------------------------------------------------------
// class CPaintDCHP
// -------------------------------------------------------------------
CPaintDCHP::CPaintDCHP(CWnd* pWnd) : CPaintDC(pWnd) // using parent constructor
{
	// defaults
	this->HPGridImage.ucLength = 1;
	this->HPGridImage.ucWeigth = 1;
}

CPaintDCHP::CPaintDCHP(CWnd* pWnd, stGridImage HPGridImage) : CPaintDC(pWnd) // using parent constructor
{
	this->HPGridImage = HPGridImage;
}


CPaintDCHP::~CPaintDCHP()
{
}

void CPaintDCHP::SetGridImageStruc(stGridImage HPGridImage)
{
	this->HPGridImage.ucLength = HPGridImage.ucLength;
	this->HPGridImage.ucWeigth = HPGridImage.ucWeigth;
}


void CPaintDCHP::Circle(int x, int y)
{
	// Paint
	WORD uiThick = this->HPGridImage.ucWeigth / 2;

	this->Ellipse(x - uiThick, y + uiThick, x + uiThick, y - uiThick);

}

void CPaintDCHP::Node(int x, int y)
{
	// Save Pen prev
	CPen * Pen_Prev(GetCurrentPen());
	

	// Set Pen style
	CPen Pen_Act(PS_SOLID, 4, RGB(50, 100, 200));

	this->SelectObject(Pen_Act);

	// Paint
	this->Circle(x, y);

	// Restore Pen prev
	this->SelectObject(Pen_Prev);

}

