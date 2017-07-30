// Sector.cpp

// \ INFO
// *******************************************************************
// Class for Hex_Plot Sector representation
// define Coord point in Node
// CGridHP <- CPlotHP <- CNodeHP <- CSector
// *******************************************************************

// implementation file


//////////////////////////////////////////////////////////////////////
// Includes
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Sector.h"


// ===================================================================
// class CSector
// ===================================================================
CSector::CSector()
{
	Init();

}

CSector::CSector(POINT gridPos)
{
	Init();

	m_position = gridPos;
}


CSector::~CSector()
{
}

void CSector::Init()
{
	// > Default Values

	// init properties
	// default
	POINT initCoord;
	initCoord.x = 0;
	initCoord.y = 0;

	m_position = initCoord;

	// [addition]

}
