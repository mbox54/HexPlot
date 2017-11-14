// Sector.h

// \ INFO
// *******************************************************************
// Class for Hex_Plot Sector representation
// define Coord point in Node
// CGridHP <- CPlotHP <- CNodeHP <- CSector
// *******************************************************************


// interface file


#pragma once

//////////////////////////////////////////////////////////////////////
// Includes
//////////////////////////////////////////////////////////////////////



// ===================================================================
// class CSector
// ===================================================================
class CSector
{
public:
	// standard constructor
	CSector();
	CSector(POINT gridPos);

	~CSector();

	// > Properties
	POINT m_position;		// graphic /unused

	BYTE m_altitude;


	// > Methods
	// Init
	void Init();
};

