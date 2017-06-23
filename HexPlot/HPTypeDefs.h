// HPTypeDefs.h : header file

// \ INFO
// *******************************************************************
// Header File for Hex_Plot Typedefs
// and other soursec
// *******************************************************************


#pragma once

#include <vector>
//////////////////////////////////////////////////////////////////////
// TypeDef
//////////////////////////////////////////////////////////////////////

typedef unsigned char BYTE;

typedef struct stHPGridParams
{
	BYTE ucLength;
	BYTE ucWeigth;

	WORD uiOXPadding;
	WORD uiOYPadding;
};


typedef struct stHPPlotParams
{
	BYTE ucLength;
	BYTE ucWeigth;

};

typedef struct stHPNodeParams
{
	BYTE ucLength;
	BYTE ucWeigth;

};

typedef struct stHPSectorParams
{
	BYTE ucLength;
	BYTE ucWeigth;

};

typedef struct stHPCanvasParams
{
	stHPGridParams		HPGridParams;
	stHPPlotParams		HPPlotParams;
	stHPNodeParams		HPNodeParams;
	stHPSectorParams	HPSectorParams;
};

typedef struct stHPNodeGraphInfo
{
	BYTE Value;

};

typedef std::vector < std::vector< stHPNodeGraphInfo > > vectGraphGridInfo;