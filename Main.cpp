#include "SudokuPuzzle.h"

// This is a basic starting point for you to use to implement your Sudoku solver
int main(int argc, char **) {
	float totalTime = 0;
	SudokuPuzzle puzzle;
	puzzle.Solve("sudoku_puzzle.txt");
	totalTime += puzzle.time;
	SudokuPuzzle puzzle2;
	puzzle2.Solve("sudoku_puzzle2.txt");
	totalTime += puzzle2.time;
	SudokuPuzzle puzzle3;
	puzzle3.Solve("sudoku_puzzle3.txt");
	totalTime += puzzle3.time;
	SudokuPuzzle puzzle4;
	puzzle4.Solve("sudoku_puzzle4.txt");

	/*cout << (totalTime / 3 ) << "\r\n";*/
	system("pause");

	return 0;
}
