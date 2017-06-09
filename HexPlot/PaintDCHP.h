// PaintDCHP.h

// \ INFO
// *******************************************************************
// Class for PaintDC HexPlot Graphics
// include additional procedures for HexPlot graphics
// based on CPaintDC
// *******************************************************************

// interface file


#pragma once

//////////////////////////////////////////////////////////////////////
// Includes
//////////////////////////////////////////////////////////////////////

#include "afxwin.h"
#include "HPTypeDefs.h"

//////////////////////////////////////////////////////////////////////
// Definitions
//////////////////////////////////////////////////////////////////////

//

// -------------------------------------------------------------------
// class CPaintDCHP
// -------------------------------------------------------------------
class CPaintDCHP : public CPaintDC
{
public:
	// standard constructor
	CPaintDCHP(CWnd* pWnd);

	CPaintDCHP(CWnd* pWnd, 	stHPCanvasParams * pHPCanvasParams);

	~CPaintDCHP();


	// properties
	stHPCanvasParams * pHPCanvasParams;

	// events
	void SetGridImageStruc(stHPCanvasParams * pHPGridImage);

	void Circle(int x, int y);
	
	// node
	void Node(POINT Coord);
	void Node(int x, int y);

	// line
	// NOTE: FORMAT: Line to XY / 0 = O, 1 = P(os), -1 = N(eg)
	// NOTE: HexPlot relations: [+1 0], [-1 0], [0 +1], [0 -1], [+1 -1], [-1 +1].  
	void LinePO(int x, int y);


};

