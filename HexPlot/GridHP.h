// GridHP.h

// \ INFO
// *******************************************************************
// Class for Hex_Plot Grid representation
// define Grid common logic
// Grid include Nodes
// CGridHP <- CPlotHP <- CNodeHP <- CSector
// *******************************************************************

// interface file


#pragma once

//////////////////////////////////////////////////////////////////////
// Includes
//////////////////////////////////////////////////////////////////////

#include "NodeHP.h"
#include "StaticHP.h"

#include "Trasse.h"

#include <vector>
//

// side size Parameter
#define SIDESIZE 20

// ===================================================================
// class CGridHP
// ===================================================================

class CGridHP
{
public:
	// standard constructor
	CGridHP();
	CGridHP(CStaticHP * p_CanvasHP);


	// > Properties
	// > > Node Container
	POINT m_gridSize;
	std::vector < std::vector< CNodeHP > > v_Nodes;

	// Trasse of Nodes
	CTrasse m_Trasse;

	// > > Graphics
	// Canvas sourse
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


	// > > Logic
	// Node OP
	void AddNode();
	void LoadNode(POINT gridPos);

	void AddWeg();
	void StraightWeg(POINT nodeFirst, POINT nodeLast, CWeg * p_wegOutput);
	void EstimateWegCost(POINT nodeFirst, POINT nodeLast);

	// > > Graphic
	void FormGraphInfo();
	void PaintGrid();

	// Test
	void Test();


	~CGridHP();
};

