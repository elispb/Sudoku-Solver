#pragma once

#include "cell.h"
#include "cellGroup.h"
#include <iostream>
#include <fstream>
using namespace std;

class SudokuPuzzle
{
public:
	SudokuPuzzle(void);
	~SudokuPuzzle(void);

	int FindCandidates(cellGroup cells[], /*cell &target,*/ int x) ;
	bool FindHiddenSingles(cellGroup cells[],  cell &target, int x) ;
	int SolveHiddenValues(int changes);
	void FindNakedSingles(cell &targetCell) ;
	void Solve(char filenameIn[]);
	void InspectGrid();
	float time = 0;

private:
	void Output() const;
	void Input(char filenameIn[]);
	void InitializeCells();
	cell m_grid[81];
	cellGroup block[9];
	cellGroup row[9];
	cellGroup column[9];
	int TempIndex[81];
	int gridPasses = 0;
	int solvedValues = 0;
	int unsolvedValues = 0;
	int givenValues = 0;
	int nakedSingles = 0;
	int hiddenSingles = 0;
	int cellInspections = 0;
	int candidatesConsidered = 0;
	
};

