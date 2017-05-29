// NodeHP.h

// \ INFO
// *******************************************************************
// Class for Hex_Plot Node representation
// define Node common logic
// *******************************************************************


//////////////////////////////////////////////////////////////////////
// Includes
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NodeHP.h"

// -------------------------------------------------------------------
// class CNodeHP
// -------------------------------------------------------------------
CNodeHP::CNodeHP()
{
	// init properties
	// default
	POINT initCoord;
	initCoord.x = 0;
	initCoord.y = 0;

	m_position = initCoord;
	
	// [addition]

}

CNodeHP::CNodeHP(POINT gridPos)
{
	// init properties
	// according to GridPH position
	m_position = gridPos;
}


CNodeHP::~CNodeHP()
{
}
