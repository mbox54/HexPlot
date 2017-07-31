// NodeHP.h

// \ INFO
// *******************************************************************
// Class for Hex_Plot Node representation
// define Node common logic
// Container Unit
// CGridHP <- CPlotHP <- CNodeHP <- CSector
// *******************************************************************

// interface file


#pragma once

//////////////////////////////////////////////////////////////////////
// Includes
//////////////////////////////////////////////////////////////////////

#include "Terrain.h"
#include "Sector.h"

#include <vector>


// side size Parameter
#define SIDESIZE 48				// NOTE: HexGrid Size: x12 = dozens


// -------------------------------------------------------------------
// class CNodeHP
// -------------------------------------------------------------------
class CNodeHP
{

public:
	// standard constructor
	CNodeHP();
	CNodeHP(POINT gridPos);

	~CNodeHP();


	// > Properties
	// > > Net Position
	POINT m_position;		// graphic /unused

	// Borders: Allowed directions
	BYTE v_incidence[6];

	// > > Sector Container
	// > Properties
	POINT m_gridSize;
	std::vector < std::vector< CSector > > v_Sectors;

	// > > Node Logic
	// Terrain
	CTerrain m_terrain;

	// Anlage
	


	// > Methods
	// Init
	void Init();
	void SetInit(POINT gridPos);

	// 
	void Load();

	// Sector
	void FillSectors();
	void HexToMem(POINT pt_Input, POINT * pt_Output);
	void MemToHex(POINT pt_Input, POINT * pt_Output);

	// Get Graph output Data
	void FormGraphInfo(BYTE * ucValue);




};

