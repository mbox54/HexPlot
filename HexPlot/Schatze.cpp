// Schatze.h

// \ INFO
// *******************************************************************
// ['Schatze' = 'Resource']
// Class for define 'Resource' instance
// Have automatization metods for member Unit
// *******************************************************************

// implementation file


//////////////////////////////////////////////////////////////////////
// Includes
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Schatze.h"


// -------------------------------------------------------------------
// class CSchatze
// -------------------------------------------------------------------
CSchatze::CSchatze()
{

}


CSchatze::~CSchatze()
{

}


void CSchatze::AddLinienzugKnot(stLinienzugKnot strucLinienzugKnot)
{

	// allocate memory: Sector in 2x Cell /in Vector container
	this->v_Linienzug.push_back(strucLinienzugKnot);

}

WORD CSchatze::GetLinienzugSize()
{
	WORD usTemp = this->v_Linienzug.size;

	return usTemp;

}


void CSchatze::TestInit()
{
	stLinienzugKnot strucLinienzugKnot;

	// fill test Value
	for (BYTE k = 0; k < 10; k++)
	{

		strucLinienzugKnot.xyCoord.x = k;
		strucLinienzugKnot.xyCoord.y = k;

		strucLinienzugKnot.ucPos = 0;
	}

	// place 
	this->AddLinienzugKnot(strucLinienzugKnot);

}


void CSchatze::InitLinienzugPositions()
{

}


BYTE CSchatze::DefineLinienzugCrossing()
{

}
