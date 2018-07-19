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


// INFO:
// algorithm description:
// 1. use as FIRST knot the top left knot
// 2. define position direction relate on next knot
// 3. proceed to the next knot in sequence until the end
void CSchatze::InitLinienzugPositions()
{
	// knots iterator
	// NOTE: MAX knots count = 65535
	WORD usSI = 0;

	// position direction
	// init Value = RIGHT
	BYTE ucP = RIGHT;

	// set init knot:
	// SI = 0, P(0) = Right
	this->v_Linienzug[0].ucPos = RIGHT;

	// proc knot sequence
	WORD usCount = this->v_Linienzug.capacity();

	POINT xyCoordDiff;

	while (usSI < usCount)
	{
		// go to the next knot
		usSI++;

		// define direction difference
		xyCoordDiff.x = this->v_Linienzug[usSI].xyCoord.x - this->v_Linienzug[usSI - 1].xyCoord.x;
		xyCoordDiff.y = this->v_Linienzug[usSI].xyCoord.y - this->v_Linienzug[usSI - 1].xyCoord.y;

		// define Position direction
		// INFO:
		// knot sequence has adjacent knot with MAX difference = 1
		switch (ucP)
		{
		case NOINIT:
			// err case
			break;


		case UP:
			if (xyCoordDiff.x = 1)
			{
				// [ X+ ]



			}
			else if (xyCoordDiff.x = -1)
			{
				// [ X- ]


			}
			
			

			break;


		case LEFT:

			break;


		case DOWN:

			break;


		case RIGHT:

			break;


		default:
			break;
		}

	}



}


BYTE CSchatze::DefineLinienzugCrossing()
{

}
