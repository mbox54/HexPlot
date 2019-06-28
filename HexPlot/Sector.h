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
// support
#include "globals.h"

// load/save xml file
#include "external\tinyxml2.h"


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
	//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	// Init
	void Init();



	// File OPs
	void Save();
	void Load();

	// test
	void DebugBillet01(void);

};

