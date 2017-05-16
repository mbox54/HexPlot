// LibHashFunct.cpp

// \ INFO
// *******************************************************************
// Library source with service Functions
// Functions for calculate/perform HASH Operations
// *******************************************************************

// implementation file

#include "stdafx.h"
#include "HexAlgorithm.h"


void FillGrid(BYTE * v_HexGrid, BYTE ucSize)
{
	for (int i = 0; i < ucSize; i++)
	{
		for (int j = 0; j < ucSize; j++)
		{
			*(v_HexGrid + i*ucSize + j) = 5;
		}
	}

}