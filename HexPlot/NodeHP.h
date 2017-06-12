// NodeHP.h

// \ INFO
// *******************************************************************
// Class for Hex_Plot Node representation
// define Node common logic
// Container Unit
// *******************************************************************

// interface file


#pragma once

//////////////////////////////////////////////////////////////////////
// Includes
//////////////////////////////////////////////////////////////////////

#include "Terrain.h"


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
	POINT m_position;		// graphic /unused

	// BORDER: Allow directions
	BYTE v_incidence[6];

	// Terrain
	CTerrain m_terrain;

	// Anlage
	


	// > Methods
	// Init
	void Init();
	void SetInit(POINT gridPos);

	// 
	void Load();

	// Get Graph output Data
	void FormGraphInfo(BYTE * ucValue);




};

