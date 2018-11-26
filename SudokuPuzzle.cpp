#include "SudokuPuzzle.h"
#include <Windows.h>
#include <list>
SudokuPuzzle::SudokuPuzzle(void) :
	TempIndex(),
	gridPasses(0),
	solvedValues(0),
	unsolvedValues(0),
	givenValues(0),
	nakedSingles(0),
	hiddenSingles(0),
	cellInspections(0),
	candidatesConsidered(0)
{
	m_grid[81];// = cell();
	block[9];// = cellGroup();
	row[9];// = cellGroup();
	column[9];// = cellGroup();	
}
SudokuPuzzle::~SudokuPuzzle(void)
{
}
void SudokuPuzzle::Solve(char filenameIn[])
{
	Input(filenameIn);// You will need to read the values of the Sudoku puzzle into your data structure
	solvedValues = givenValues;
	InitializeCells();
	LARGE_INTEGER start, end, frequency;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start);
	// Solve the puzzle
	for (int i = 0; i < 9; ++i)
	{
		FindCandidates(column, /*target,*/ i);
		FindCandidates(row, /*target,*/ i);
		FindCandidates(block, /*target,*/ i);
	}
	for (int i = 0; i < 81; ++i)
	{
		if (!m_grid[i].GetCellValue())
		{
			candidatesConsidered += m_grid[i].GetCandidateList().size();
		}
	}
	InspectGrid();
	QueryPerformanceCounter(&end);
	time = (end.QuadPart - start.QuadPart) / (static_cast<float> (frequency.QuadPart));
	cout << "\r\nBest Solution Found";
	int counter = 0;
	for (int i = 0; i < 3; i++)
	{
		cout << "\r\n\r\n";
		for (int j = 0; j < 3; j++)
		{
			cout << "\r\n";
			for (int k = 0; k < 3; k++)
			{
				cout << "\t";
				for (int l = 0; l < 3; l++)
				{
					cout << m_grid[counter].GetCellValue() << " ";
					counter++;
				}
			}
		}
	}
	cout << "\r\n\r\n";
	cout << "Time Taken: " << time << "\r\n";
	cout << "Grid Passes: " << gridPasses << "\r\n";
	cout << "Solved Values: " << solvedValues << "\r\n";
	cout << "Unsolved Values: " << 81 - solvedValues << "\r\n";
	cout << "Found Naked Values: " << nakedSingles << "\r\n";
	cout << "Found Hidden Values: " << hiddenSingles << "\r\n";
	cout << "Given Values: " << givenValues << "\r\n";
	cout << "Cells inspected: " << cellInspections << "\r\n";
	cout << "Candidates considered: " << candidatesConsidered << "\r\n";
	Output();  // Output the solved puzzle
}
void SudokuPuzzle::InspectGrid()
{	
	++gridPasses;
	int changes = 0;
	for (int i = 0; i < 81; ++i)
	{
		cell& target = m_grid[i];
		if (!target.GetMGiven())
		{
			++cellInspections;
			/*if (FindCandidates(column, target, target.GetMColumn()) || FindCandidates(row, target, target.GetMRow()) || FindCandidates(block, target, target.GetMBlock()))
			{*/
			if (target.GetCandidateList().size() == 1)
			{
				FindNakedSingles(target);
				++solvedValues;
				++nakedSingles;
				++changes;
				if (solvedValues == 81)
				{
					return;
				}
				candidatesConsidered += FindCandidates(column, /*target,*/ target.GetMColumn());
				candidatesConsidered += FindCandidates(row, /*target,*/ target.GetMRow());
				candidatesConsidered += FindCandidates(block, /*target,*/ target.GetMBlock());
			}
		}
	}
	if (solvedValues != 81)
	{
		++gridPasses;
		changes += SolveHiddenValues(changes);
	}
	if (solvedValues != 81 && changes != 0)
	{
		InspectGrid();
	}
}
int SudokuPuzzle::SolveHiddenValues(int changes)
{
	for (int i = 0; i < 81; ++i)
	{
		cell& target = m_grid[i];
		if (!target.GetMGiven())
		{
			cellInspections++;

			if (FindHiddenSingles(column, target, target.GetMColumn()) || FindHiddenSingles(row, target, target.GetMRow()) || FindHiddenSingles(block, target, target.GetMBlock()))
			{
				++solvedValues;
				++hiddenSingles;
				++changes;
				if (solvedValues == 81)
				{
					m_grid[i] = target;
					return changes;
				}
				candidatesConsidered += FindCandidates(column, /*target,*/ target.GetMColumn());
				candidatesConsidered += FindCandidates(row, /*target,*/ target.GetMRow());
				candidatesConsidered += FindCandidates(block, /*target,*/ target.GetMBlock());
			}
			m_grid[i] = target;
		}
	}
	return changes;
}
void SudokuPuzzle::Input(char filenameIn[])
{
	char ch;
	int x = 0;
	fstream fin(filenameIn, fstream::in);
	while (fin >> ch)
	{
		TempIndex[x] = (int)ch - 48;
		if (TempIndex[x] > 0)
		{
			++givenValues;
		}
		++x;
	}
}
void SudokuPuzzle::Output() const
{
	ofstream fout("sudoku_solution.txt"); // DO NOT CHANGE THE NAME OF THIS FILE
	if (fout.is_open())
	{
		int counter = 0;
		for (int y = 0; y < 9; ++y)
		{
			for (int x = 0; x < 9; ++x)
			{
				fout << m_grid[counter].GetCellValue() << " ";
				++counter;
			}
			fout << endl;
		}
		fout.close();
	}
}
int SudokuPuzzle::FindCandidates(cellGroup cells[], /*cell &targetCell,*/ int x)
{
	int candidatesCon = 0;
	for (int i = 0; i < 9; ++i)
	{
		cell& InspectedCell = cells[x].GetCell(i);
		if (InspectedCell.GetMGiven()) // Remove solved and given from candidate list
		{
			for (int j = 0; j < 9; ++j)
			{
				cell& updateCell = cells[x].GetCell(j);
				if (!updateCell.GetMGiven())
				{
					if (updateCell.SetCandidateList(cells[x].GetCell(i).GetCellValue()))
					{
						candidatesCon += updateCell.GetCandidateList().size();
					}
				}
			}
		}
	}
	return candidatesCon;
}
void SudokuPuzzle::FindNakedSingles(cell &targetCell)
{
	targetCell.SetValue(targetCell.GetCandidateList().front());
}
bool SudokuPuzzle::FindHiddenSingles(cellGroup cells[], cell &targetCell, int x)
{
	int TargetM_Id = targetCell.GetMID();
	int ListLength = targetCell.GetCandidateList().size();
	for (int j = 0; j < ListLength; ++j)
	{
		candidatesConsidered++;
		int targetCandidate = targetCell.GetCandidateList().at(j);
		bool hiddenSingleFound = true;
		for (int i = 0; i < 9; i++) //For all cells in cell group
		{
			if (!cells[x].GetCell(i).GetMGiven() && cells[x].GetCell(i).GetMID() != TargetM_Id) //If its not itself or solved
			{
				for (int j =0; j < cells[x].GetCell(i).GetCandidateList().size(); ++j)
				//for each (int candidate in cells[x].GetCell(i).GetCandidateList()) //For each candidate in cell
				{
					int candidate = cells[x].GetCell(i).GetCandidateList()[j];
					
					if (targetCandidate == candidate)
					{
						hiddenSingleFound = false;
						break;
					}
				}
				if (!hiddenSingleFound)
				{
					break;
				}
			}
		}
		if (hiddenSingleFound)
		{
			targetCell.SetValue(targetCandidate);
			return true;
		}
	}
	return false;
}
void SudokuPuzzle::InitializeCells()
{
	int columnNum = 0;
	int rowNum = 0;
	int blockCol = 0;
	int blockNum = 0;
	int blockCounter = 0;
	int b = 0;
	for (int i = 0; i < 81; ++i)
	{
		int number = TempIndex[i];
		//Track location in puzzle
		if (columnNum > 8)
		{
			columnNum = 0;
			rowNum++;
		}
		if (blockCounter > 2)
		{
			blockCol++;
			blockNum++;
			blockCounter = 0;

			if (blockCol > 2)
			{
				blockCol = 0;
				if (rowNum <= 2)
				{
					blockNum = 0;
				}
				else if (rowNum <= 5)
				{
					blockNum = 3;
				}
				else if (rowNum <= 8)
				{
					blockNum = 6;
				}
			}
		}
		//Create cell with location
		m_grid[i] = cell(number, i, rowNum, columnNum, blockNum);
		m_grid[i].InitialiseCandidateList();
		//Add cell to cellGroups
		if (rowNum == 0 || rowNum == 3 || rowNum == 6)
		{
			block[blockNum].SetCell(blockCounter, &m_grid[i]);
		}
		else if (rowNum == 1 || rowNum == 4 || rowNum == 7)
		{
			block[blockNum].SetCell((blockCounter + 3), &m_grid[i]);
			b++;
		}
		else if (rowNum == 2 || rowNum == 5 || rowNum == 8)
		{
			block[blockNum].SetCell((blockCounter + 6), &m_grid[i]);
		}
		column[columnNum].SetCell(rowNum, &m_grid[i]);
		row[rowNum].SetCell(columnNum, &m_grid[i]);
		//Inrement counters for position
		++columnNum;
		++blockCounter;
	}
}