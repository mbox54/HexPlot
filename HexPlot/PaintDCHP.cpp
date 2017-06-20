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

CPaintDCHP::CPaintDCHP(CWnd* pWnd, POINT * p_gridSize, stHPCanvasParams * pHPGridImage) : CPaintDC(pWnd) // using parent constructor
{
	this->p_gridSize = p_gridSize;
	this->pHPCanvasParams = pHPGridImage;
}


CPaintDCHP::~CPaintDCHP()
{
}

void CPaintDCHP::SetGridImageStruc(stHPCanvasParams * pHPGridImage)
{
	this->pHPCanvasParams = pHPGridImage;

}

// clause
void CPaintDCHP::Circle(POINT Coord)
{
	Circle(Coord.x, Coord.y);
	
}


void CPaintDCHP::Circle(int x, int y)
{
	// Localize Vars	
	WORD uiThick = this->pHPCanvasParams->HPNodeParams.ucWeigth;

	uiThick /= 2;

	// Paint
	this->Ellipse(x - uiThick, y + uiThick, x + uiThick, y - uiThick);

}

// clause
void CPaintDCHP::Node(POINT Coord)
{
	this->Node(Coord.x, Coord.y);
}


void CPaintDCHP::Node(int x, int y) //!!!! Replace int -> WORD //? POINT has int
{
	// Save Pen prev
	CPen * Pen_Prev(GetCurrentPen());
	
	// Set Pen style
	CPen Pen_Act(PS_SOLID, 4, RGB(50, 100, 200));

	this->SelectObject(Pen_Act);

	// Localize Vars
	POINT ProcCoor;
	BYTE ucLineLength = this->pHPCanvasParams->HPGridParams.ucLength;

	// Define Canvas Coord
	ProcCoor.x = 100 + x * ucLineLength;
	ProcCoor.y = 600 - y * ucLineLength * 1.732;

	// > Paint
	this->Circle(ProcCoor);

	// Restore Pen prev
	this->SelectObject(Pen_Prev);

}

void CPaintDCHP::LinePO(int x, int y)
{

}

// NOTE: 
// FORMAT: 
// HexPlot Line Types : 
// 0 = [0  +1], 
// 1 = [+1  0], 
// 2 = [0  -1], 
// 3 = [+1 -1], 
// 4 = [-1  0], 
// 5 = [-1 +1].
void CPaintDCHP::Line(int x, int y, BYTE LineType)
{
	// Localize Vars
	POINT ProcCoor;
	BYTE ucLineLength = this->pHPCanvasParams->HPGridParams.ucLength;

	// Define Canvas Coord
	ProcCoor.x = 100 + x * ucLineLength;
	ProcCoor.y = 600 - y * ucLineLength * 1.732;

	// Move Pen Pointer to Node Center
	MoveTo(ProcCoor);

	// Line to define direction
	switch (LineType)
	{
	case 0:
		// ProcCoor.x  NONE
		ProcCoor.y -= ucLineLength * 1.732 / 2;

		break;

	case 1:
		ProcCoor.x += ucLineLength / 2;
		// ProcCoor.y NONE

		break;

	case 2:
		// ProcCoor.x  NONE
		ProcCoor.y += ucLineLength * 1.732 / 2;

		break;

	case 3:
		ProcCoor.x += ucLineLength / 2;
		ProcCoor.y += ucLineLength * 1.732 / 2;

		break;

	case 4:
		ProcCoor.x -= ucLineLength / 2;
		// ProcCoor.y NONE

		break;

	case 5:
		ProcCoor.x -= ucLineLength / 2;
		ProcCoor.y -= ucLineLength * 1.732 / 2;

		break;

	default:

		// err case
		break;
	}

	LineTo(ProcCoor);

}

// clause
void CPaintDCHP::Line(POINT Coord, BYTE LineType)
{
	Line(Coord.x, Coord.y, LineType);

}


// Paint Grid
void CPaintDCHP::Grid()
{
	// each Node of Grid
	for (WORD k_x = 0; k_x < this->p_gridSize->x; k_x ++)
	{
		for (BYTE k_y = 0; k_y < this->p_gridSize->y; k_y ++)
		{
			// Lines
			for (BYTE k_line = 0; k_line < 6; k_line++)
			{
				// if 
				this->Line(k_x, k_y, k_line);
			}

			// Node
			this->Node(k_x, k_y);
		}
	}

}

