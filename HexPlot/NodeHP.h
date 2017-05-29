// NodeHP.h

// \ INFO
// *******************************************************************
// Class for Hex_Plot Node representation
// define Node common logic
// *******************************************************************

// interface file


#pragma once

//////////////////////////////////////////////////////////////////////
// Includes
//////////////////////////////////////////////////////////////////////

//


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


	// properties
	POINT m_position;		// graphic /unused

	// // net
	BYTE Incidence[6];


	// // plot


	// events


};

