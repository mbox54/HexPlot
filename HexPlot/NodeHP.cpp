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
	this->m_position = gridPos;
}


void CNodeHP::Init(POINT gridPos)
{
	//

}


void CNodeHP::SetInit(POINT gridPos)
{
	// init properties
	// according to GridPH position
	m_position = gridPos;
}

// Load Values from DataBase
void CNodeHP::Load()
{
	// Using [m_position] to define DB Cell to Load

}


CNodeHP::~CNodeHP()
{
}
