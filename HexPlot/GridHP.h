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

#include "StaticHP.h"
//

// -------------------------------------------------------------------
// class CGridHP
// -------------------------------------------------------------------
class CGridHP
{
public:
	// standard constructor
	CGridHP();


	// properties
	// // Canvas source
	CStaticHP * p_CanvasHP;

	// > Events
	// Init
	void SetCanvas(CStaticHP * p_CanvasHP);
	void Init(CStaticHP * p_CanvasHP);

	// Graphic
	void AddNode();

	~CGridHP();
};

