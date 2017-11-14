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
CNodeHP::CNodeHP()
{
	// init
	Init();

}

CNodeHP::CNodeHP(POINT gridPos)
{
	Init();

	this->m_position = gridPos;
}


void CNodeHP::Init()
{
	// > Default Values

	// init properties
	// default
	POINT initCoord;
	initCoord.x = 0;
	initCoord.y = 0;

	m_position = initCoord;

	// [addition]

	// incidence /all/
	for (BYTE k = 0; k < 6; k++)
	{
		this->v_incidence[k] = 1;
	}

	// > Fill Sectors
	FillSectors();

}


void CNodeHP::SetInit(POINT gridPos)
{
	// init properties
	// according to GridPH position
	m_position = gridPos;
}

void CNodeHP::Save()
{
	// > Form Document
	tinyxml2::XMLDocument WDocument;

	// > Form XML Header
	char * str_XMLSpec = "xml version=\"1.0\" encoding=\"windows - 1251\" standalone=\"yes\"";
	tinyxml2::XMLDeclaration* WDeclaration = WDocument.NewDeclaration(str_XMLSpec);
	WDocument.LinkEndChild(WDeclaration);

	tinyxml2::XMLComment* CmntDeclaration = WDocument.NewComment("WAST Node file structure");
	WDocument.LinkEndChild(CmntDeclaration);

	// > Form Title Part
	tinyxml2::XMLElement* El_Root = WDocument.NewElement("WAST");
	WDocument.LinkEndChild(El_Root);

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
	tinyxml2::XMLElement* El_Tit_Sectors = WDocument.NewElement("Nodes");
	El_Title->InsertEndChild(El_Tit_Sectors);

	tinyxml2::XMLElement* El_Tit_Sectors_X = WDocument.NewElement("X");
	El_Tit_Sectors_X->SetText(m_gridSize.x);
	El_Tit_Sectors->InsertEndChild(El_Tit_Sectors_X);

	tinyxml2::XMLElement* El_Tit_Sectors_Y = WDocument.NewElement("Y");
	El_Tit_Sectors_Y->SetText(m_gridSize.y);
	El_Tit_Sectors->InsertEndChild(El_Tit_Sectors_Y);


	// > Form Body
	tinyxml2::XMLComment* CmntBody = WDocument.NewComment("Part: Body");
	El_Root->InsertEndChild(CmntBody);

	tinyxml2::XMLElement* El_Body = WDocument.NewElement("BODY");
	El_Root->InsertEndChild(El_Body);

	// > Body Content
	// Node
	for (BYTE ky = 0; ky < m_gridSize.y; ky++)
	{
		for (BYTE kx = 0; kx < m_gridSize.x; kx++)
		{
			tinyxml2::XMLElement* El_Sector = WDocument.NewElement("Sector");
			El_Sector->SetAttribute("Y", ky);
			El_Sector->SetAttribute("X", kx);
			El_Sector->SetText(200);
			El_Sector->InsertEndChild(El_Sector);
		}

	}

	// > Save Document
	WDocument.SaveFile("C:\\wast\\WastNode.xml");
}

// Load Values from DataBase
void CNodeHP::Load()
{
	// Using [m_position] to define DB Cell to Load


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

	this->m_gridSize = pt_Size;

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
			CSector Sector(pt_CoordHex);

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


void CNodeHP::HexToMem(POINT pt_Input, POINT * pt_Output)
{
	if (pt_Input.y < this->m_gridSize.y / 2)
	{
		// [SECTOR 4]

		pt_Output->x = pt_Input.x - (this->m_gridSize.y / 2 - pt_Input.y);
	}
	else
	{
		pt_Output->x = pt_Input.x;
	}

	pt_Output->y = pt_Input.y;
}


void CNodeHP::MemToHex(POINT pt_Input, POINT * pt_Output)
{
	if (pt_Input.y < this->m_gridSize.y / 2)
	{
		// [SECTOR 4]

		pt_Output->x = pt_Input.x + (this->m_gridSize.y / 2 - pt_Input.y);
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
