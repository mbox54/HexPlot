// NodeHP.cpp

// \ INFO
// *******************************************************************
// Class for Hex_Plot Node representation
// define Node common logic
// *******************************************************************

// implementation file


//////////////////////////////////////////////////////////////////////
// Includes
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NodeHP.h"

// ===================================================================
// class CNodeHP
// ===================================================================

//////////////////////////////////////////////////////////////////////
// Constructor, init section
//
// NOTE:
// Object is part of complex structure:
// Grid - Plot - [Node] - Sector
// Construction algorithm:
// 1) Construct Node instance
// 2) init property instance with default
// 3) load properties from file NodeXXXYYY
// 4) fill sub-element vector: Sectors
CNodeHP::CNodeHP()
{
	// init
	Init();

}

// CASE: 
// create with defined specific net position
CNodeHP::CNodeHP(POINT pt_NetPos)
{
	Init();
	
	// > Load Values
	this->m_position = pt_NetPos;

	// > Load Values
	// XML FILE OP
	//!debug
	/////////////////////////////////////////////////////
	// NO FILE INITIATION CASE
	/////////////////////////////////////////////////////
	// DEBUG: use test config Billet
	DebugBillet01();

	Load();
	
	// > Place Net: create Sectors
	PlaceNet();
}


void CNodeHP::Init()
{
	// ## Default Values
	// NOTE: need when load op failed
	// Init properties	

	// [m_position]
	POINT initCoord;
	initCoord.x = 0;
	initCoord.y = 0;

	m_position = initCoord;

	// [m_gridSize]
	POINT pt_Size;
	pt_Size.x = SIDESIZE;
	pt_Size.y = SIDESIZE;

	this->m_NetSize = pt_Size;

	// [v_incidence]
	for (BYTE k = 0; k < 6; k++)
	{
		this->v_incidence[k] = 1;
	}


}


void CNodeHP::SetInit(POINT gridPos)
{
	// init properties
	// according to GridPH position
	m_position = gridPos;
}


//////////////////////////////////////////////////////////////////////
// FILE XML OPs
//
void CNodeHP::Save()
{
	// # Form Document
	tinyxml2::XMLDocument WDocument;

	// # Form XML Header
	char * str_XMLSpec = "xml version=\"1.0\" encoding=\"windows - 1251\" standalone=\"yes\"";
	tinyxml2::XMLDeclaration* WDeclaration = WDocument.NewDeclaration(str_XMLSpec);
	WDocument.LinkEndChild(WDeclaration);

	tinyxml2::XMLComment* CmntDeclaration = WDocument.NewComment("WAST Node file structure");
	WDocument.LinkEndChild(CmntDeclaration);
	
	// # Form Wast root element
	tinyxml2::XMLElement* El_Root = WDocument.NewElement("WAST");
	WDocument.LinkEndChild(El_Root);

	tinyxml2::XMLElement* WastPart = WDocument.NewElement("Part");
	WastPart->SetText("NODE");
	El_Root->InsertEndChild(WastPart);

	// # Form Title Part
	tinyxml2::XMLComment* CmntTitle = WDocument.NewComment("Part: Title");
	El_Root->InsertEndChild(CmntTitle);

	tinyxml2::XMLElement* El_Title = WDocument.NewElement("TITLE");
	El_Root->InsertEndChild(El_Title);

	// > Title Content
	// Description
	tinyxml2::XMLElement* El_Tit_Desc = WDocument.NewElement("Descr");
	El_Tit_Desc->SetText("Wast File, contained Node structure filled with data");
	El_Title->InsertEndChild(El_Tit_Desc);

	// Date
	tinyxml2::XMLElement* El_Tit_Date = WDocument.NewElement("Date");
	El_Tit_Date->SetText("Save PROC Date: 141117 15.14");
	El_Title->InsertEndChild(El_Tit_Date);

	// Sectors
	tinyxml2::XMLElement* El_Tit_Sectors = WDocument.NewElement("Sectors");
	El_Title->InsertEndChild(El_Tit_Sectors);

	tinyxml2::XMLElement* El_Tit_Sectors_X = WDocument.NewElement("X");
	El_Tit_Sectors_X->SetText(m_NetSize.x);
	El_Tit_Sectors->InsertEndChild(El_Tit_Sectors_X);

	tinyxml2::XMLElement* El_Tit_Sectors_Y = WDocument.NewElement("Y");
	El_Tit_Sectors_Y->SetText(m_NetSize.y);
	El_Tit_Sectors->InsertEndChild(El_Tit_Sectors_Y);


	// > Form Body
	tinyxml2::XMLComment* CmntBody = WDocument.NewComment("Part: Body");
	El_Root->InsertEndChild(CmntBody);

	tinyxml2::XMLElement* El_Body = WDocument.NewElement("BODY");
	El_Root->InsertEndChild(El_Body);

	// > Body Content
	// Terrain
	tinyxml2::XMLElement* El_Body_Terrain = WDocument.NewElement("Terrain");
	El_Body->InsertEndChild(El_Body_Terrain);

	tinyxml2::XMLElement* El_Body_Terrain_Type = WDocument.NewElement("TerrainType");
	El_Body_Terrain_Type->SetText(m_terrain.m_TerrainType);
	El_Body_Terrain->InsertEndChild(El_Body_Terrain_Type);


	// > Save Document
	// Form specific Filename (NodeY05X08)
	char strFileName[128];
	strcpy(strFileName, m_stGlobals.cDirectoryPath);
	strcat(strFileName, "\\");
	strcat(strFileName, m_strWastName);
	strcat(strFileName, "\\Node");
	
	strcat(strFileName, "Y");
	char str_buf[8];
	_itoa(m_position.y, str_buf, 10);
	strcat(strFileName, str_buf);

	strcat(strFileName, "X");
	_itoa(m_position.x, str_buf, 10);
	strcat(strFileName, str_buf);

	// Create Node directory
	CreateDirectory((CString)strFileName, NULL);

	strcat(strFileName, "\\Node.xml");

	WDocument.SaveFile(strFileName);
}

// Load Values from DataBase
// NOTE:
// Using [m_position] to define DB Cell to Load
void CNodeHP::Load()
{
	// > Form Document
	tinyxml2::XMLDocument WDocument;

	// > Load Document
	char strFileName[128];
	strcpy(strFileName, m_stGlobals.cDirectoryPath);
	strcat(strFileName, "\\");
	strcat(strFileName, m_strWastName);
	strcat(strFileName, "\\Node");

	strcat(strFileName, "Y");
	char str_buf[8];
	_itoa(m_position.y, str_buf, 10);
	strcat(strFileName, str_buf);

	strcat(strFileName, "X");
	_itoa(m_position.x, str_buf, 10);
	strcat(strFileName, str_buf);

	strcat(strFileName, "\\Node.xml");

	WDocument.LoadFile(strFileName);

	// > Parse Title Part
	tinyxml2::XMLElement* El_Root = WDocument.FirstChildElement("WAST");
	tinyxml2::XMLElement* El_Title = El_Root->FirstChildElement("TITLE");

	// > Title Content
	// grid size: Sectors 
	tinyxml2::XMLElement* El_Tit_Nodes = El_Title->FirstChildElement("Sectors");

	// - property: size
	tinyxml2::XMLElement* El_Tit_Nodes_X = El_Tit_Nodes->FirstChildElement("X");
	int iVal = 0;
	El_Tit_Nodes_X->QueryIntText(&iVal);
	m_NetSize.x = iVal;

	tinyxml2::XMLElement* El_Tit_Nodes_Y = El_Tit_Nodes->FirstChildElement("Y");
	El_Tit_Nodes_Y->QueryIntText(&iVal);
	m_NetSize.y = iVal;

}


void CNodeHP::DebugBillet01(void)
{
	// > Set Sector-Grid Size
	POINT pt_Size;
	pt_Size.x = 1;
	pt_Size.y = 1;

	this->m_NetSize = pt_Size;

	// > Save
	Save();
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
void CNodeHP::PlaceNet()
{
	// > Fill Rows
	POINT pt_NetCoords;

	for (WORD usCoorY = 0; usCoorY < this->m_NetSize.y; usCoorY++)
	{
		// Allocate memory: Vector for Row /in Sector Vector container
		this->v_Sectors.push_back(std::vector<CSector>());

		// Fill Cols
		for (WORD usCoorX = 0; usCoorX < this->m_NetSize.x; usCoorX++)
		{
			// define Coord to set
			POINT CoordMem;
			CoordMem.y = usCoorY;
			CoordMem.x = usCoorX;

			//this->MemToHex(CoordMem, &pt_NetCoords);

			// create Sector instance
			CSector Sector(m_position, CoordMem);

			// allocate memory: Sector in 2x Cell /in Vector container
			this->v_Sectors[usCoorY].push_back(Sector);

			// Load Node Values
			//this->LoadNode(CoordGrid);

		}//for (WORD usCoorX
	}//for (WORD usCoorY

}


// -------------------------------------------------------------------
// Sector
// -------------------------------------------------------------------
void CNodeHP::FillSectors()
{
	// FORMAT:
	// Hex Grid positioning
	// y: 0 - i - N/2, x: 0 - i - N/2 = NULL, x: N/2 - i - N = VALL
	// y: N/2 - i - N, x: 0 - i - N/2 = VALL, x: N/2 - i - N = NULL
	// STRUC: v_Sectors[Y][X]

	// > Set Grid Size
	POINT pt_Size;
	pt_Size.x = SIDESIZE;
	pt_Size.y = SIDESIZE;

	this->m_NetSize = pt_Size;

	// > Fill
	// Define HexCoords
	POINT pt_CoordHex;
		

	BYTE ucXFirst = pt_Size.x / 2;
	BYTE ucXLength = pt_Size.x / 2;

	BYTE act = 1;
	char sign = 1;

	// > Proceed Coords
	pt_CoordHex.y = 0;
	while (act != 0)
	{		
		// Proc mode
		// Note: 2 modes: 1 = 0--N/2; 2 = N/2--N. 
		if (act == 1)
		{
			// [MODE 1]

			// check mode change
			if (pt_CoordHex.y > pt_Size.y / 2 - 1)
			{
				// [CHANGE]

				sign = -1;

				act = 2;
			}
		}//then /if (act == 1)
		else
		{
			if (act == 2)
			{
				// [MODE 2]

				// check mode change
				if (pt_CoordHex.y > pt_Size.y - 1)
				{
					// [EXIT]

					act = 0;
				}
			}//if (act == 2)			
		}//else /if (act == 1)

		// Allocate memory: Vector for Row /in Sector Vector container
		this->v_Sectors.push_back(std::vector<CSector>());

		// Proceed Row: iterate Cols
		BYTE ucXLast = ucXFirst + ucXLength;

		pt_CoordHex.x = ucXFirst;
		while (pt_CoordHex.x < ucXLast)
		{
			// > Proc Coord
			// Create Sector instance / init with Hex Coord
			CSector Sector(m_position, pt_CoordHex);

			// allocate memory: Sector in 2x Cell /in Vector container
			this->v_Sectors[pt_CoordHex.y].push_back(Sector);

			pt_CoordHex.x++;
		}

		// Correct Col
		ucXFirst -= sign;
		ucXLength += sign;

		pt_CoordHex.y++;

	}//while (act != 0)

}


// INFO:
// support methods
// need for packing hex-performed coords in decard-performed memory matrix
//
// FORMAT:
// Hex Grid positioning
// y: 0 - i - N/2, x: 0 - i - N/2 = NULL, x: N/2 - i - N = VALL
// y: N/2 - i - N, x: 0 - i - N/2 = VALL, x: N/2 - i - N = NULL
// so HexFormat Net is Set in Hexagonal form
//	##+++##
//	#+++++#
//	+++++++
//	#+++++#
//	##+++##
void CNodeHP::HexToMem(POINT pt_Input, POINT * pt_Output)
{
	if (pt_Input.y < this->m_NetSize.y / 2)
	{
		// [SECTOR 4]

		pt_Output->x = pt_Input.x - (this->m_NetSize.y / 2 - pt_Input.y);
	}
	else
	{
		pt_Output->x = pt_Input.x;
	}

	pt_Output->y = pt_Input.y;
}

// INFO:
// support methods
// need for packing hex-performed coords in decard-performed memory matrix
void CNodeHP::MemToHex(POINT pt_Input, POINT * pt_Output)
{
	if (pt_Input.y < this->m_NetSize.y / 2)
	{
		// [SECTOR 4]

		pt_Output->x = pt_Input.x + (this->m_NetSize.y / 2 - pt_Input.y);
	}
	else
	{
		pt_Output->x = pt_Input.x;
	}

	pt_Output->y = pt_Input.y;
}


void CNodeHP::FormGraphInfo(BYTE * ucValue)
{
	*ucValue = this->m_terrain.m_TerrainType;
}


CNodeHP::~CNodeHP()
{

}
