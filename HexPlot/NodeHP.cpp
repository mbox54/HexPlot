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
	// init
	Init();

}

CNodeHP::CNodeHP(POINT gridPos)
{
	Init();

	this->m_position = gridPos;
}


void CNodeHP::Init()
{
	// > Default Values

	// init properties
	// default
	POINT initCoord;
	initCoord.x = 0;
	initCoord.y = 0;

	m_position = initCoord;

	// [addition]

	// incidence /all/
	for (BYTE k = 0; k < 6; k++)
	{
		this->v_incidence[k] = 1;
	}

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

void CNodeHP::FormGraphInfo(BYTE * ucValue)
{
	*ucValue = this->m_terrain.m_TerrainType;
}


CNodeHP::~CNodeHP()
{

}
