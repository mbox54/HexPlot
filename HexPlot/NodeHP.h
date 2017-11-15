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

#include "external\tinyxml2.h"

#include <vector>


// side size Parameter
#define SIDESIZE 12				// NOTE: HexGrid Size: x12 = dozens


// -------------------------------------------------------------------
// class CNodeHP
// -------------------------------------------------------------------
class CNodeHP
{

public:
	// standard constructor
	CNodeHP();
	CNodeHP(POINT gridPos);


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


	// Sector
	void PlaceNet();
	void FillSectors();
	void HexToMem(POINT pt_Input, POINT * pt_Output);
	void MemToHex(POINT pt_Input, POINT * pt_Output);

	// Get Graph output Data
	void FormGraphInfo(BYTE * ucValue);


	// File OPs
	void Save();
	void Load();


	~CNodeHP();

};

