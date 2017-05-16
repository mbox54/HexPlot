// StaticHP.h

// \ INFO
// *******************************************************************
// Class for HexPlot Graphical procedure
// include structures and methods for picturing
// based on CStatic
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

#define OP_SUCCESS				0x00
#define OP_FAILED				0x01


// -------------------------------------------------------------------
// class CStaticHP
// -------------------------------------------------------------------
class CStaticHP : public CStatic
{
public:
	// standard constructor
	CStaticHP();

	~CStaticHP();

	// properties
	WORD uiSize;
	WORD uiPaintMode;

	BYTE v_TestBase[10][10] = 
	{
		{ 0,0,0,0,0,0,0,0,0,0 },	// 0
		{ 0,0,0,0,0,0,0,0,0,0 },	// 1
		{ 0,0,0,0,0,0,0,0,0,0 },	// 2
		{ 0,0,0,0,0,0,0,0,0,0 },	// 3
		{ 0,0,0,0,0,0,0,0,0,0 },	// 4
		{ 0,0,0,0,0,0,0,0,0,0 },	// 5
		{ 0,0,0,0,0,0,0,0,0,0 },	// 6
		{ 0,0,0,0,0,0,0,0,0,0 },	// 7
		{ 0,0,0,0,0,0,0,0,0,0 },	// 8
		{ 0,0,0,0,0,0,0,0,0,0 },	// 9
	};

	// methods
	void InitTest();
	void PaintGrid();
	void PaintGrid2();

	// events
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
};

