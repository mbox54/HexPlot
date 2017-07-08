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
	m_Trasse.Add(nodeWeg);

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



// Stor WegKnot sequence of Straight WegPath
// NOTE:
// *******************************************
// [#] HexPlot Line Types : 
// 0 = [0  +1], 
// C = [+1  0], 
// 2 = [+1 -1], 
// 3 = [0  -1], 
// 4 = [-1  0], 
// 5 = [-1 +1].
//
//
// [#] exist N direction cases:
// direct:	case |1|, |3| = X-coord; case |0|, |3| = Y-coord
// combine: case |2|, |5| = Z-coord
// 
//
// [#] /dX/ | /dY/  defines:
// dX > 0 & dY < 0, dX < 0 & dY > 0 = Z-coord
// other = X-, Y-coord.
//
// [#] algorithm with Dijkstra method
// *******************************************
void CGridHP::StraightWeg(POINT nodeFirst, POINT nodeLast)
{
	// define vars, init
	POINT aPos = nodeFirst;		// start
	POINT zPos = nodeLast;		// finish

	int dX;						// delta
	int dY;						// delta

	// repeat sequentially for each StraightWeg WegKnot needed
	// Step by step
	BYTE act = 1;
	while (act)
	{
		// > Define dX | dY
		dX = zPos.x - aPos.x;	// delta
		dY = zPos.y - aPos.y;	// delta

		// > Check end cycle
		if ((dX == 0) && (dY == 0))
		{
			// [FINAL NODE HAS BEING ARRIVED]

			act = 0;
		}
		else
		{
			// [WAY PROCEED]

			// > Check OZ inclusion: combine case
			if ( ( (dX < 0) && (dY > 0) ) || ( (dX > 0) && (dY < 0) ) )
			{
				// [INCLUDE OZ]

				// check direction
				if (dX > 0)
				{
					// [POS]: HPDir = 2

					// move to new Pos
					aPos.x++;
					aPos.y--;
				}
				else
				{
					// [NEG]: HPDir = 5

					// move to new Pos
					aPos.x--;
					aPos.y++;
				}
			}//then: [INCLUDE OZ]/ Check OZ inclusion: combine case
			else
			{
				// [NOT INCLUDE OZ]
				// simple case

				// > Check OX POS Dir
				if (dX > 0)
				{
					// [POS]: HPDir = 1

					// move to new Pos
					aPos.x++;
				}
				else
				{
					// > Check OX NEG Dir
					if (dX < 0)
					{					
						// [NEG]: HPDir = 4

						// move to new Pos
						aPos.x--;
					}
					else
					{
						// [NOT INCLUDE OX]

						// > Check OY POS Dir
						if (dY > 0)
						{
							// [POS]: HPDir = 0

							// move to new Pos
							aPos.y++;
						}
						else
						{
							// > Check OY NEG Dir
							if (dY < 0)
							{
								// [NEG]: HPDir = 3

								// move to new Pos
								aPos.y--;
							}
							else
							{
								// [NOT INCLUDE OY]

								// strange condition:
								// no OZ, no OX, no OY. MUST dX = dY = 0.

								act = 0;
							}// > Check OY NEG Dir
						}// > Check OY POS Dir
					}// > Check OX NEG Dir
				}// > Check OX POS Dir
			}//else/ > Check OZ inclusion: combine case

			// > Add WegKnot
			//

		}// > Check end cycle, if ((dX == 0) && (dY == 0))

	}//while (act)
}

// Stor WegKnot sequence of best WegPath
// Estimate minimal cost to complete path [nodeFirst -> nodeLast]
void CGridHP::EstimateWegCost(POINT nodeFirst, POINT nodeLast)
{


}


