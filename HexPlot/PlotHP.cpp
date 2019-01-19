// PlotHP.cpp

// \ INFO
// *******************************************************************
// Class for Hex_Plot Plot representation
// define Plot common logic
// Container Unit
// CGridHP <- CPlotHP <- CNodeHP <- CSector
// *******************************************************************


// implementation file


//////////////////////////////////////////////////////////////////////
// Includes
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "PlotHP.h"


// ===================================================================
// class CPlotHP
// ===================================================================
CPlotHP::CPlotHP()
{
	Init();
}


CPlotHP::CPlotHP(POINT gridPos)
{
	Init();

	this->m_position = gridPos;
}


CPlotHP::~CPlotHP()
{

}


void CPlotHP::Init(void)
{
	// > Default Values

	// init properties
	// default
	POINT initCoord;
	initCoord.x = 0;
	initCoord.y = 0;

	m_position = initCoord;

	// [addition]

	// incidence /none/
	for (BYTE k = 0; k < 6; k++)
	{
		this->v_incidence[k] = 0;
	}

	// > Load Values
	// ExpandGrid();

}


void CPlotHP::Load(void)
{

}


void CPlotHP::AddNode(POINT gridPos)
{
	// > check appropriate Count of line
	while (this->v_NodesHP.size() < gridPos.y)
	{
		// [NEED TO ADD LINE]

		// allocate memory: Vector for Row /in Node Vector container
		this->v_NodesHP.push_back(std::vector<CNodeHP>());
	}

	// create Node instance
	CNodeHP NodeHP(gridPos);

	// allocate memory: Node in 2x Cell /in Node Vector container
	this->v_NodesHP[gridPos.y].push_back(NodeHP);
}

// Place Defined Node-Unit Net in Memory
// NOTE:
// FORMAT:
// Y = RowNumber, X = ColNumber
//
// vector structure v_Nodes has specific:
// Allocate Row ---> Allocate Col, Allocate Col, Allocate Col,
// Allocate Row ---> Allocate Col, Allocate Col, Allocate Col,
// Allocate Row ---> Allocate Col, Allocate Col, Allocate Col,
// ...
// so v_Nodes[Y][X] has (Y, X) placement order
void CPlotHP::ExpandGrid(void)
{
	// > Fill Rows
	POINT CoordGrid;

	for (WORD uiCoorY = 0; uiCoorY < this->m_gridSize.y; uiCoorY++)
	{
		// Fill Cols
		for (WORD uiCoorX = 0; uiCoorX < this->m_gridSize.x; uiCoorX++)
		{
			// define Coord to set
			CoordGrid.y = uiCoorY;
			CoordGrid.x = uiCoorX;

			AddNode(CoordGrid);

			// Load Node Values
			//this->LoadNode(CoordGrid);
		}//for (WORD uiCoorX
	}//for (WORD uiCoorY

}