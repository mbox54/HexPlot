// GridHP.h

// \ INFO
// *******************************************************************
// Class for Hex_Plot Grid representation
// define Grid common logic
// Grid include Nodes
// *******************************************************************


//////////////////////////////////////////////////////////////////////
// Includes
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GridHP.h"



// -------------------------------------------------------------------
// class CGridHP
// -------------------------------------------------------------------
CGridHP::CGridHP()
{
	// Init
	Init();
}

CGridHP::CGridHP(CStaticHP * p_CanvasHP)
	: p_CanvasHP(p_CanvasHP)
{
	// 
	Init();
}


void CGridHP::SetCanvas(CStaticHP * p_CanvasHP)
{
	this->p_CanvasHP = p_CanvasHP;
}

void CGridHP::Init()
{
	// init Grid Vector
	POINT CoordGrid;

	for (WORD uiCoorX = 0; uiCoorX < 20; uiCoorX++)
	{
		for (WORD uiCoorY = 0; uiCoorY < 20; uiCoorY++)
		{
			// > Fill
			// Create new Node
			CoordGrid.x = uiCoorX;
			CoordGrid.y = uiCoorY;

			this->AddNode(CoordGrid);
		}
	}

}


void CGridHP::AddNode()
{
	CNodeHP NodeHP;
}


void CGridHP::AddNode(POINT gridPos)
{
	// > Create Node
	CNodeHP NodeHP(gridPos);

	// set Node
	this->v_Nodes[gridPos.x][gridPos.y] = NodeHP;

	// > Paint Node
	// calc Coords
	// // get Graph parameters
	//p_CanvasHP->

	//p_CanvasHP->PaintGrid();
}

CGridHP::~CGridHP()
{
}
