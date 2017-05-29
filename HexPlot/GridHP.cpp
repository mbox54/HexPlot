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
}


void CGridHP::SetCanvas(CStaticHP * p_CanvasHP)
{
	this->p_CanvasHP = p_CanvasHP;
}

void CGridHP::Init(CStaticHP * p_CanvasHP)
{
	// set canvas address
	SetCanvas(p_CanvasHP);

	// other
}

void CGridHP::AddNode()
{
	p_CanvasHP->PaintGrid();
}

CGridHP::~CGridHP()
{
}
