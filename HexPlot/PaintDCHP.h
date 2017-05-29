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


//////////////////////////////////////////////////////////////////////
// Definitions
//////////////////////////////////////////////////////////////////////



typedef struct stGridImage
{
	BYTE ucLength;
	BYTE ucWeigth;

};

// -------------------------------------------------------------------
// class CPaintDCHP
// -------------------------------------------------------------------
class CPaintDCHP : public CPaintDC
{
public:
	// standard constructor
	CPaintDCHP(CWnd* pWnd);

	CPaintDCHP(CWnd* pWnd, stGridImage HPGridImage);

	~CPaintDCHP();


	// properties
	stGridImage HPGridImage;

	// events
	void SetGridImageStruc(stGridImage HPGridImage);

	void Circle(int x, int y);
	
	// node
	void Node(int x, int y);

	// line
	// NOTE: FORMAT: Line to XY / 0 = O, 1 = P(os), -1 = N(eg)
	// NOTE: HexPlot relations: [+1 0], [-1 0], [0 +1], [0 -1], [+1 -1], [-1 +1].  
	void LinePO(int x, int y);


};

