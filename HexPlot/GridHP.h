// GridHP.h

// \ INFO
// *******************************************************************
// Class for Hex_Plot Grid representation
// define Grid common logic
// Grid include Nodes
// *******************************************************************

// interface file


#pragma once

//////////////////////////////////////////////////////////////////////
// Includes
//////////////////////////////////////////////////////////////////////

#include "NodeHP.h"				// Elements of Grid Container
#include "StaticHP.h"			// Graphic Control

#include "Trasse.h"				// Ways Routing

//#include "external\tinyxml2.h"	// XML-file Save/Load

#include "tinyxml2.h"	// XML-file Save/Load

#include <vector>				// Vector-class support
//

// side size Parameter
#define SIDESIZE 20

// -------------------------------------------------------------------
// class CGridHP
// -------------------------------------------------------------------

class CGridHP
{
public:
	// standard constructor
	CGridHP();
	CGridHP(CStaticHP * p_CanvasHP);


	// > Properties
	POINT m_gridSize;

	// Node Container
	std::vector < std::vector< CNodeHP > > v_Nodes;

	// Trasse of Nodes
	CTrasse m_Trasse;

	//  Canvas source
	CStaticHP * p_CanvasHP;

	// localize Variable usage
	vectGraphGridInfo * p_GridGraphInfo;	// pointer to /set of Nodes Info/ from Canvas	


	// > Methods
	// Init
	void Init();

	// InProc
	void SetGridSize(POINT gridSize);
	void SetCanvas(CStaticHP * p_CanvasHP);
	void SetGridGraphInfo();


	// Logic
	// // Node OP
	void AddNode();
	void LoadNode(POINT gridPos);

	void AddWeg();
	void EstimateWegCost(POINT nodeFirst, POINT nodeLast);

	// Graphic
	void FormGraphInfo();
	void PaintGrid();

	// File Procs
	void Save();
	void Load();


	~CGridHP();
};

