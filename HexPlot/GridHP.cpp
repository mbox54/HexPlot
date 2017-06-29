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
void CGridHP::FormGraphInfo()
{
	// NOTE: use GraphTrasm struc DataType

	// localize Grid size
	POINT grph_Size = this->m_gridSize;

	// construct Graph Grid-Net Info
	POINT CoordGrid;

	for (WORD uiCoorX = 0; uiCoorX < grph_Size.x; uiCoorX++)
	{
		// allocate memory: Vector for Row /in NodeGraphInfo struc container
		this->p_GridGraphInfo->push_back(std::vector<stHPNodeGraphInfo>());

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
			this->p_GridGraphInfo->at(uiCoorX).push_back(HPNodeGraphInfo);
		}
	}//for (WORD uiCoorX / WORD uiCoorX)

}

// Paint Grid on Graphic Control
// NOTE: use Canvas vars for PROC Graph parameters, TRASM to Paint
void CGridHP::PaintGrid()
{
	// > Define Grid_Net Set-of-Nodes
	// forming Node Graph Info
	this->FormGraphInfo();

	// > Call subordinate: Paint PROC
	this->p_CanvasHP->PaintGrid();
}


CGridHP::~CGridHP()
{

}


void CGridHP::SetGridSize(POINT gridSize)
{
	this->m_gridSize = gridSize;
}

// Set control /Canvas/
void CGridHP::SetCanvas(CStaticHP * p_CanvasHP)
{
	// Set Canvas source
	this->p_CanvasHP = p_CanvasHP;

	// Set Graph Info source from Canvas
	SetGridGraphInfo();
}

// Set struc /Values: size, Nodes/
void CGridHP::SetGridGraphInfo()
{
	// set Pointer /v_GridGraphInfo/ to Variable MemAddr [INPUT]
	this->p_GridGraphInfo = &this->p_CanvasHP->v_GridGraphInfo;

	// set Pointer /GridSize/ to Variable MemAddr [OUTPUT]
	this->p_CanvasHP->p_gridSize = &this->m_gridSize;

}

// Construct & Fill v_Nodes
void CGridHP::Init()
{
	// > Init Grid Vector
	POINT Point_temp;
	Point_temp.x = 12;
	Point_temp.y = 12;

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

	// create Node path
	CWeg nodeWeg;

	// fill weg
	for (BYTE k = 0; k < 5; k++)
	{
		// form wegKnot
		stWegKnot wegKnot;

		wegKnot.xyCoord.x = k;
		wegKnot.xyCoord.y = k;

		wegKnot.uiNumber = k;

		// set el
		nodeWeg.Add(wegKnot);
	}

	//m_Trasse.Add

}


void CGridHP::AddNode()
{
	CNodeHP NodeHP;
}

// Load Grid: Size, v_Nodes From File/Base
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


