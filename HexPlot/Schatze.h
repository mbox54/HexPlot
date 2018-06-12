// Schatze.h

// \ INFO
// *******************************************************************
// ['Schatze' = 'Resource']
// Class for define 'Resource' instance
// Have automatization metods for member Unit
// *******************************************************************

// interface file


#pragma once

//////////////////////////////////////////////////////////////////////
// Includes
//////////////////////////////////////////////////////////////////////

#include <vector>

//////////////////////////////////////////////////////////////////////
// Typedefs
//////////////////////////////////////////////////////////////////////

// Linienzug Knot
// ['Linienzug' = 'Kontur']
//
// NOTE:
// FORMAT:
// # 'Pos' Values: 
// - UP			1
// - LEFT		2
// - DOWN		3
// - RIGHT		4
typedef struct stLinienzugKnot
{
	POINT xyCoord;	

	BYTE ucPos;
};


// -------------------------------------------------------------------
// class CSchatze
// -------------------------------------------------------------------
class CSchatze
{
public:
	// standard constructor
	CSchatze();

	~CSchatze();

	// > Properties
	BYTE m_ucResouceType;

	std::vector<stLinienzugKnot> v_Linienzug;

	// > Methods
	// starter initialization, define Pos Values 
	void InitLinienzugPositions();

	// define State of 'Point' crossing 'Kontur' on demand
	BYTE DefineLinienzugCrossing();

};

