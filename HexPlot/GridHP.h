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
	std::vector < std::vector<CNodeHP> > v_Nodes;

	//std::vector<std::vector<CNodeHP>> v_Nodes(std::vector<CNodeHP>, std::vector<CNodeHP>(2, 1));
	//CNodeHP v_Nodes[20][20];

	//  Canvas source
	CStaticHP * p_CanvasHP;

	// > Events
	// Init
	void Init();

	// InProc
	void SetCanvas(CStaticHP * p_CanvasHP);


	// Logic
	// // Node OP
	void AddNode();
	void AddNode(POINT gridPos);

	~CGridHP();
};

