// GridHP.cpp

// \ INFO
// *******************************************************************
// Class for Hex_Plot Grid representation
// define Grid common logic
// Grid include Nodes
// *******************************************************************

// implementation file


//////////////////////////////////////////////////////////////////////
// Includes
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GridHP.h"


// ===================================================================
// class CGridHP
// ===================================================================

//////////////////////////////////////////////////////////////////////
// Constructor, init section
//
CGridHP::CGridHP()
{
	// Init
	Init();

	// XML FILE OP
	//!debug
	/////////////////////////////////////////////////////
	// NO FILE INITIATION CASE
	/////////////////////////////////////////////////////
	// DEBUG: use test config Billet
	DebugBillet01();

	Load();

	// > Place Net: create Nodes
	PlaceNet();


	// !debug
	//// create Node path
	//CWeg nodeWeg;

	//// fill weg
	//for (BYTE k = 0; k < 5; k++)
	//{
	//	// form wegKnot
	//	stWegKnot wegKnot;

	//	wegKnot.xyCoord.x = k;
	//	wegKnot.xyCoord.y = k;

	//	wegKnot.uiNumber = k;

	//	// set el
	//	nodeWeg.Add(wegKnot);
	//}

	////m_Trasse.Add
	//m_Trasse.Add(nodeWeg);
}

// CASE: 
// use VS Win Static control as canvas for graphics
// NOTE:
// this realisation attach Canvas upon OnInit stage!
CGridHP::CGridHP(CStaticHP * p_CanvasHP)
	: p_CanvasHP(p_CanvasHP)
{
	// Init
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
	// ## Default Values
	// NOTE: need when load op failed
	// Init properties	
	// [m_strWastName]
	strcpy(m_strWastName, "unnamed");

	// [m_gridSize] 
	POINT pt_Size;
	pt_Size.x = SIDESIZE;
	pt_Size.y = SIDESIZE;

	m_gridSize = pt_Size;

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
void CGridHP::PlaceNet()
{
	// > Fill Rows
	POINT CoordGrid;

	for (WORD uiCoorY = 0; uiCoorY < this->m_gridSize.y; uiCoorY++)
	{
		// allocate memory: Vector for Row /in Node Vector container
		this->v_Nodes.push_back(std::vector<CNodeHP>());

		// Fill Cols
		for (WORD uiCoorX = 0; uiCoorX < this->m_gridSize.x; uiCoorX++)
		{
			// define Coord to set
			CoordGrid.y = uiCoorY;
			CoordGrid.x = uiCoorX;
			
			// create Node instance
			CNodeHP NodeHP(CoordGrid);

			// allocate memory: Node in 2x Cell /in Node Vector container
			this->v_Nodes[uiCoorY].push_back(NodeHP);

			// Load Node Values
			this->LoadNode(CoordGrid);
		}//for (WORD uiCoorX
	}//for (WORD uiCoorY

}
 

//////////////////////////////////////////////////////////////////////
// Common methods section
//
void CGridHP::AddNode()
{
	CNodeHP NodeHP;
}

// Load Grid: Size, v_Nodes From File/Base
void CGridHP::LoadNode(POINT gridPos)
{
	this->v_Nodes[gridPos.y][gridPos.x].Load();

	// set Node
	//v_Nodes

	

	// > Paint Node
	// calc Coords
	// // get Graph parameters
	//p_CanvasHP->

	//p_CanvasHP->PaintGrid();
}



void CGridHP::AddWeg()
{

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
void CGridHP::StraightWeg(POINT nodeFirst, POINT nodeLast, CWeg * p_wegOutput)
{
	// define vars, init
	POINT aPos = nodeFirst;		// start
	POINT zPos = nodeLast;		// finish

	int dX;						// delta
	int dY;						// delta

	stWegKnot wegKnot;			// temp struc for WegKnot fill OP
	WORD k = 0;					// cycle increment

	// > Add init First Node
	// fill Knot struc
	wegKnot.uiNumber = k;
	wegKnot.xyCoord = aPos;

	// add to OutputVar
	p_wegOutput->Add(wegKnot);

	k++;

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
			// fill Knot struc
			wegKnot.uiNumber = k;
			wegKnot.xyCoord = aPos;

			// add to OutputVar
			p_wegOutput->Add(wegKnot);

			k++;

		}// > Check end cycle, if ((dX == 0) && (dY == 0))

	}//while (act)
}

// Stor WegKnot sequence of best WegPath
// Estimate minimal cost to complete path [nodeFirst -> nodeLast]
void CGridHP::EstimateWegCost(POINT nodeFirst, POINT nodeLast)
{


}

//////////////////////////////////////////////////////////////////////
// FILE XML OPs
//
void CGridHP::Save()
{
	// # Form Document
	tinyxml2::XMLDocument WDocument;

	// # Form XML Header
	char * str_XMLSpec = "xml version=\"1.0\" encoding=\"windows - 1251\" standalone=\"yes\"";
	tinyxml2::XMLDeclaration* WDeclaration = WDocument.NewDeclaration(str_XMLSpec);
	WDocument.LinkEndChild(WDeclaration);

	tinyxml2::XMLComment* CmntDeclaration = WDocument.NewComment("WAST Grid file structure");
	WDocument.LinkEndChild(CmntDeclaration);

	// # Form Wast root element
	tinyxml2::XMLElement* El_Root = WDocument.NewElement("WAST");
	WDocument.LinkEndChild(El_Root);

	tinyxml2::XMLElement* WastPart = WDocument.NewElement("Part");
	WastPart->SetText("GRID");
	El_Root->InsertEndChild(WastPart);

	// # Form Title Part
	tinyxml2::XMLComment* CmntTitle = WDocument.NewComment("Part: Title");
	El_Root->InsertEndChild(CmntTitle);

	tinyxml2::XMLElement* El_Title = WDocument.NewElement("TITLE");
	El_Root->InsertEndChild(El_Title);

	// > Title Content
	// Description
	tinyxml2::XMLElement* El_Tit_Desc = WDocument.NewElement("Descr");
	El_Tit_Desc->SetText("Wast File, contained Grid structure filled with data");
	El_Title->InsertEndChild(El_Tit_Desc);

	// Date
	tinyxml2::XMLElement* El_Tit_Date = WDocument.NewElement("Date");
	El_Tit_Date->SetText("Save PROC Date: 141117 10.00");
	El_Title->InsertEndChild(El_Tit_Date);

	// Node grid size
	tinyxml2::XMLElement* El_Tit_Nodes = WDocument.NewElement("Nodes");
	El_Title->InsertEndChild(El_Tit_Nodes);

	tinyxml2::XMLElement* El_Tit_Nodes_X = WDocument.NewElement("X");
	El_Tit_Nodes_X->SetText(m_gridSize.x);
	El_Tit_Nodes->InsertEndChild(El_Tit_Nodes_X);

	tinyxml2::XMLElement* El_Tit_Nodes_Y = WDocument.NewElement("Y");
	El_Tit_Nodes_Y->SetText(m_gridSize.y);
	El_Tit_Nodes->InsertEndChild(El_Tit_Nodes_Y);


	// # Form Body
	tinyxml2::XMLComment* CmntBody = WDocument.NewComment("Part: Body");
	El_Root->InsertEndChild(CmntBody);

	tinyxml2::XMLElement* El_Body = WDocument.NewElement("BODY");
	El_Root->InsertEndChild(El_Body);

	// # Body Content
	// Node
	for (BYTE ky = 0; ky < m_gridSize.y; ky++)
	{
		for (BYTE kx = 0; kx < m_gridSize.x; kx++)
		{
			tinyxml2::XMLElement* El_Node = WDocument.NewElement("Node");
			El_Node->SetAttribute("Y", ky);
			El_Node->SetAttribute("X", kx);
			El_Node->SetText(100);
			El_Body->InsertEndChild(El_Node);
		}
		
	}

	// # Save Document
	char strFileName[128];
	strcpy(strFileName, m_stGlobals.cDirectoryPath);
	strcat(strFileName, "\\");
	strcat(strFileName, m_strWastName);

	// Create Node directory
	CreateDirectory((CString)strFileName, NULL);

	strcat(strFileName, "\\Grid.xml");

	WDocument.SaveFile(strFileName);
}


void CGridHP::Load()
{
	// > Form Document
	tinyxml2::XMLDocument WDocument;

	// > Load Document
	char strFileName[128];
	strcpy(strFileName, m_stGlobals.cDirectoryPath);
	strcat(strFileName, "\\");
	strcat(strFileName, m_strWastName);
	strcat(strFileName, "\\Grid.xml");

	WDocument.LoadFile(strFileName);

	// > Parse Title Part
	tinyxml2::XMLElement* El_Root = WDocument.FirstChildElement("WAST");
	tinyxml2::XMLElement* El_Title = El_Root->FirstChildElement("TITLE");

	// > Title Content
	// grid size: Plots
	// NOTE:
	// need to perform Node -> Plot
	tinyxml2::XMLElement* El_Tit_Nodes = El_Title->FirstChildElement("Nodes");

	// - property: size
	tinyxml2::XMLElement* El_Tit_Nodes_X = El_Tit_Nodes->FirstChildElement("X");
	int iVal = 0;
	El_Tit_Nodes_X->QueryIntText(&iVal);
	m_gridSize.x = iVal;

	tinyxml2::XMLElement* El_Tit_Nodes_Y = El_Tit_Nodes->FirstChildElement("Y");
	El_Tit_Nodes_Y->QueryIntText(&iVal);
	m_gridSize.y = iVal;

}


//////////////////////////////////////////////////////////////////////
// Debug, Test section
//
void CGridHP::DebugBillet01(void)
{
	// > Set Grid size work instance
	// Set Grid Size
	POINT Point_temp;
	Point_temp.x = 1;
	Point_temp.y = 1;

	this->m_gridSize = Point_temp;

	// 

	// > Save
	// set instance Name
	strcpy(m_strWastName, "System1");

	Save();
}

// Test functionality
void CGridHP::Test()
{
	// test FILE OPs
	//Save();

	//this->v_Nodes[1][2].Save();

	// test StraightWeg PROC
	POINT coorFirs;
	POINT coorLast;

	coorFirs.x = 5;
	coorFirs.y = 5;

	coorLast.x = 10;
	coorLast.y = 10;

	CWeg weg_tmp;

	this->StraightWeg(coorFirs, coorLast, &weg_tmp);
}