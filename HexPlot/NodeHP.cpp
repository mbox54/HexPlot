// NodeHP.cpp

// \ INFO
// *******************************************************************
// Class for Hex_Plot Node representation
// define Node common logic
// *******************************************************************

// implementation file


//////////////////////////////////////////////////////////////////////
// Includes
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NodeHP.h"

// ===================================================================
// class CNodeHP
// ===================================================================
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

	// > Fill Sectors
	FillSectors();

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

// -------------------------------------------------------------------
// Sector
// -------------------------------------------------------------------
void CNodeHP::FillSectors()
{
	// FORMAT:
	// Hex Grid positioning
	// y: 0 - i - N/2, x: 0 - i - N/2 = NULL, x: N/2 - i - N = VALL
	// y: N/2 - i - N, x: 0 - i - N/2 = VALL, x: N/2 - i - N = NULL
	// STRUC: v_Sectors[Y][X]

	// > Set Grid Size
	POINT pt_Size;
	pt_Size.x = SIDESIZE;
	pt_Size.y = SIDESIZE;

	this->m_gridSize = pt_Size;

	// > Fill
	// Define HexCoords
	POINT pt_CoordHex;
	
	

	BYTE ucXFirst = pt_Size.x / 2;
	BYTE ucXLength = pt_Size.x / 2;

	BYTE act = 1;
	char sign = 1;

	// > Proceed Coords
	pt_CoordHex.y = 0;
	while (act != 0)
	{		
		// Proc mode
		// Note: 2 modes: 1 = 0--N/2; 2 = N/2--N. 
		if (act == 1)
		{
			// [MODE 1]

			// check mode change
			if (pt_CoordHex.y > pt_Size.y / 2 - 1)
			{
				// [CHANGE]

				sign = -1;

				act = 2;
			}
		}//then /if (act == 1)
		else
		{
			if (act == 2)
			{
				// [MODE 2]

				// check mode change
				if (pt_CoordHex.y > pt_Size.y - 1)
				{
					// [EXIT]

					act = 0;
				}
			}//if (act == 2)			
		}//else /if (act == 1)

		// Allocate memory: Vector for Row /in Sector Vector container
		this->v_Sectors.push_back(std::vector<CSector>());

		// Proceed Row: iterate Cols
		BYTE ucXLast = ucXFirst + ucXLength;

		pt_CoordHex.x = ucXFirst;
		while (pt_CoordHex.x < ucXLast)
		{
			// > Proc Coord
			// Create Sector instance / init with Hex Coord
			CSector Sector(pt_CoordHex);

			// allocate memory: Sector in 2x Cell /in Vector container
			this->v_Sectors[pt_CoordHex.y].push_back(Sector);

			pt_CoordHex.x++;
		}

		// Correct Col
		ucXFirst -= sign;
		ucXLength += sign;

		pt_CoordHex.y++;

	}//while (act != 0)

}


void CNodeHP::HexToMem(POINT pt_Input, POINT * pt_Output)
{
	if (pt_Input.y < this->m_gridSize.y / 2)
	{
		// [SECTOR 4]

		pt_Output->x = pt_Input.x - (this->m_gridSize.y / 2 - pt_Input.y);
	}
	else
	{
		pt_Output->x = pt_Input.x;
	}

	pt_Output->y = pt_Input.y;
}


void CNodeHP::MemToHex(POINT pt_Input, POINT * pt_Output)
{
	if (pt_Input.y < this->m_gridSize.y / 2)
	{
		// [SECTOR 4]

		pt_Output->x = pt_Input.x + (this->m_gridSize.y / 2 - pt_Input.y);
	}
	else
	{
		pt_Output->x = pt_Input.x;
	}

	pt_Output->y = pt_Input.y;
}


void CNodeHP::FormGraphInfo(BYTE * ucValue)
{
	*ucValue = this->m_terrain.m_TerrainType;
}


CNodeHP::~CNodeHP()
{

}
