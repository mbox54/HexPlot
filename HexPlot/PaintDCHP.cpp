// PaintDCHP.cpp

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

}

CPaintDCHP::CPaintDCHP(CWnd* pWnd, stHPCanvasParams * pHPGridImage) : CPaintDC(pWnd) // using parent constructor
{
	this->pHPCanvasParams = pHPGridImage;
}


CPaintDCHP::~CPaintDCHP()
{
}

void CPaintDCHP::SetGridImageStruc(stHPCanvasParams * pHPGridImage)
{
	this->pHPCanvasParams = pHPGridImage;

}


void CPaintDCHP::Circle(int x, int y)
{
	// Paint
	WORD uiThick = this->pHPCanvasParams->HPNodeParams.ucWeigth / 2;

	this->Ellipse(x - uiThick, y + uiThick, x + uiThick, y - uiThick);

}

void CPaintDCHP::Node(POINT Coord)
{
	this->Node(Coord.x, Coord.y);
}

void CPaintDCHP::Node(int x, int y) //!!!! Replace int -> WORD
{
	// Save Pen prev
	CPen * Pen_Prev(GetCurrentPen());
	

	// Set Pen style
	CPen Pen_Act(PS_SOLID, 4, RGB(50, 100, 200));

	this->SelectObject(Pen_Act);

	// > Paint
	// calc Canvas Coords
//	WORD canv_x = 50 + x * this->

	// paint
	this->Circle(x, y);

	// Restore Pen prev
	this->SelectObject(Pen_Prev);

}

void CPaintDCHP::LinePO(int x, int y)
{

}

// NOTE: 
// FORMAT: 
// HexPlot Line Types : 
// 0 = [+1 0], 
// 1 = [-1 0], 
// 2 = [0 +1], 
// 3 = [0 -1], 
// 4 = [+1 -1], 
// 5 = [-1 +1].
void CPaintDCHP::Line(int x, int y, BYTE LineType)
{
	// Move Pen Pointer to Node Center
	MoveTo(x, y);

	// Line to define direction
	switch (LineType)
	{
	case 0:


		break;



	default:

		// err case
		break;
	}
}


void CPaintDCHP::Grid()
{

}

