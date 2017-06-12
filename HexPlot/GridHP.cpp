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


// Prepare Information for Grid -> Graphic Picture Controller
void CGridHP::FormGraphInfo(POINT * p_grph_Size, std::vector < std::vector< stHPNodeGraphInfo > > * p_NodesGraphInfo)
{
	// NOTE: use GraphTrasm struc DataType

	// define Grid size
	POINT grph_Size = this->m_gridSize;

	// construct Graph Grid-Net Info
	// (set 2nd parameter)
	POINT CoordGrid;

	for (WORD uiCoorX = 0; uiCoorX < grph_Size.x; uiCoorX++)
	{
		// allocate memory: Vector for Row /in NodeGraphInfo struc container
		p_NodesGraphInfo->push_back(std::vector<stHPNodeGraphInfo>());

		// Fill Cols
		for (WORD uiCoorY = 0; uiCoorY < grph_Size.y; uiCoorY++)
		{
			// define Coord to set
			CoordGrid.x = uiCoorX;
			CoordGrid.y = uiCoorY;

			// create NodeGraphInfo instance
			stHPNodeGraphInfo HPNodeGraphInfo;

			// Form Node Info-Value for Graph OPs
			BYTE ucNodeValue;
			this->v_Nodes[uiCoorX][uiCoorY].FormGraphInfo(&ucNodeValue);
			HPNodeGraphInfo.Value = ucNodeValue;


			// allocate memory: NodeGraphInfo in 2x Cell /in NodeGraphInfo struc Vector container
			// fill with Value
			p_NodesGraphInfo->at(uiCoorX).push_back(HPNodeGraphInfo);
		}
	}//for (WORD uiCoorX / WORD uiCoorX)

	// (set 1st parameter)
	*p_grph_Size = grph_Size;

}


void CGridHP::PaintGrid()
{
	// Set Graph Parameters

	// > Define Grid_Net Set-of-Nodes
	// use Temp instance vars for TRASM parameters
	POINT grph_Size;
	std::vector < std::vector< stHPNodeGraphInfo > > v_NodesGraphInfo;

	// forming Node Graph Info
	this->FormGraphInfo(&grph_Size, &v_NodesGraphInfo);

//	this->p_CanvasHP->v_TestBase[9][9] = 5;

	// call subordinate
//	this->p_CanvasHP->PaintGrid();
}


CGridHP::~CGridHP()
{

}


void CGridHP::SetGridSize(POINT gridSize)
{
	this->m_gridSize = gridSize;
}


void CGridHP::SetCanvas(CStaticHP * p_CanvasHP)
{
	this->p_CanvasHP = p_CanvasHP;
}

void CGridHP::Init()
{
	// > Init Grid Vector
	POINT Point_temp;
	Point_temp.x = 20;
	Point_temp.y = 20;

	this->m_gridSize = Point_temp;
	//

	// > Fill Rows
	POINT CoordGrid;

	for (WORD uiCoorX = 0; uiCoorX < this->m_gridSize.x; uiCoorX++)
	{
		// allocate memory: Vector for Row /in Node Vector container
		this->v_Nodes.push_back( std::vector<CNodeHP>() );

		// Fill Cols
		for (WORD uiCoorY = 0; uiCoorY < this->m_gridSize.y; uiCoorY++)
		{
			// define Coord to set
			CoordGrid.x = uiCoorX;
			CoordGrid.y = uiCoorY;

			// create Node instance
			CNodeHP NodeHP(CoordGrid);

			// allocate memory: Node in 2x Cell /in Node Vector container
			this->v_Nodes[uiCoorX].push_back( NodeHP );

			// Load Node Values
			this->LoadNode(CoordGrid);
		}
	}

	// !debug
	PaintGrid();

}


void CGridHP::AddNode()
{
	CNodeHP NodeHP;
}


void CGridHP::LoadNode(POINT gridPos)
{
	this->v_Nodes[gridPos.x][gridPos.y].Load();

	// set Node
	//v_Nodes

	

	// > Paint Node
	// calc Coords
	// // get Graph parameters
	//p_CanvasHP->

	//p_CanvasHP->PaintGrid();
}


