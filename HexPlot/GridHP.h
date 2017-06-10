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

#include "NodeHP.h"
#include <vector>
#include "StaticHP.h"
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
	POINT gridSize;

	// Node Container
	std::vector < std::vector< CNodeHP > > v_Nodes;


	//  Canvas source
	CStaticHP * p_CanvasHP;

	// > Methods
	// Init
	void Init();

	// InProc
	void SetGridSize(POINT gridSize);
	void SetCanvas(CStaticHP * p_CanvasHP);


	// Logic
	// // Node OP
	void AddNode();
	void LoadNode(POINT gridPos);


	// Graphic
	void PaintGrid();

	~CGridHP();
};

