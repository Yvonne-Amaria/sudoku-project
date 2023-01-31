#include <iostream>
#include <vector>
using namespace std;

//back tracking based solution to sudoku game

void Sudoku(int array[9][9]){
	cout << "________________________\n" << endl;
  
	for (int x = 0;  x < 9; x++){
		for (int y = 0; y < 9; y++)
			cout << array[x][y] << " ";
		  cout << endl;
	}
  
	cout << "________________________\n" << endl;
}

bool Placement(int array[9][9], int row, int col, int n){
	if (array[row][col] != 0) 
    return false;
  
	bool status = true;
	int gridx = (col / 3) * 3;
	int gridy = (row / 3) * 3;
  
	for (int i = 0; i < 9; i++){
		if (array[row][i] == n) { 
      status = false; 
      break; 
    }
    
		if (array[i][col] == n) { 
      status = false; 
      break; 
    }
    
		if (array[gridy + i / 3][gridx + i % 3] == n){
      status = false; 
      break; 
    }
	}
  
	return status;
}

void nextEmpty(int array[9][9], int row, int col, int& NextRow, int& NextCol){

	int NextIndex = 9 * 9 + 1;
	for (int i = row * 9 + col + 1; i < 9 * 9; i++){
		if (array[i / 9][i % 9] == 0) {

			NextIndex = i;
			break;
		}
	}
  
	NextRow = NextIndex / 9;
	NextCol = NextIndex % 9;
}

void copyArray(int array[9][9], int arrCopy[9][9]) {
	for (int x = 0; x < 9; x++)
		for (int y = 0; y < 9; y++)
			arrCopy[x][y] = array[x][y];
}

vector<int> findPlaceables(int array[9][9], int row, int col) {
	vector<int> placebles = {};
	for (int n = 1; n <= 9; n++)
		if (Placement(array, row, col, n))       placebles.push_back(n);
  
	return placebles;
}

//identifying number checkpoints
bool SudokuSolution(int array[9][9], int row, int col){
	if (row > 8) 
    return true;
  
	if (array[row][col] != 0) {
		int NextRow, NextCol;
		nextEmpty(array, row, col, NextRow, NextCol);
    
		return SudokuSolution(array, NextRow,NextCol);
	}
  
//Check placements of numbers for reorder
	vector <int> placebles = findPlaceables(array, row, col);

	if (placebles.size() == 0) {
		
		return false;
	};

	bool status = false;
	for (int i = 0; i < placebles.size(); i++){
		int n = placebles[i];
		int arrCopy[9][9];
		copyArray(array, arrCopy);
		
		arrCopy[row][col] = n;
		int NextRow = row;
		int NextCol = col;
		nextEmpty(arrCopy, row, col, NextRow, NextCol);
    
		if (SudokuSolution(arrCopy, NextRow, NextCol)){
			copyArray(arrCopy, array);
			status = true;
			break;
		}
	}
	return status;
}

//argv function creating/executing argument for backtracking
int main(int argc, char** argv){
	
  int board1[9][9] = {
		{6, 5, 0, 8, 7, 3, 0, 9, 0},
    {0, 0, 3, 2, 5, 0, 0, 0, 8},
    {9, 8, 0, 1, 0, 4, 3, 5, 7},
    {1, 0, 5, 0, 0, 0, 0, 0, 0},
    {4, 0, 0, 0, 0, 0, 0, 0, 2},
    {0, 0, 0, 0, 0, 0, 5, 0, 3},
    {5, 7, 8, 3, 0, 1, 0, 2, 6},
    {2, 0, 0, 0, 4, 8, 9, 0, 0},
    {0, 9, 0, 6, 2, 5, 0, 8, 1}
	};
  
	int board2[9][9] = {
		{3, 0, 6, 5, 0, 8, 4, 0, 0}, 
    {5, 2, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 8, 7, 0, 0, 0, 0, 3, 1}, 
    {0, 0, 3, 0, 1, 0, 0, 8, 0}, 
    {9, 0, 0, 8, 6, 3, 0, 0, 5}, 
    {0, 5, 0, 0, 9, 0, 6, 0, 0}, 
    {1, 3, 0, 0, 0, 0, 2, 5, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 7, 4}, 
    {0, 0, 5, 2, 0, 6, 3, 0, 0}
	};

  int board3[9][9] = {
		{5, 3, 0, 0, 7, 0, 0, 0, 0},
    {6, 0, 0, 1, 9, 5, 0, 0, 0},
    {0, 9, 8, 0, 0, 0, 0, 6, 0},
    {8, 0, 0, 0, 6, 0, 0, 0, 3},
    {4, 0, 0, 8, 0, 3, 0, 0, 1},
    {7, 0, 0, 0, 2, 0, 0, 0, 6},
    {0, 6, 0, 0, 0, 0, 2, 8, 0},
    {0, 0, 0, 4, 1, 9, 0, 0, 5},
    {0, 0, 0, 0, 8, 0, 0, 7, 9}
	};

  int board4[9][9] = {
    {3, 8, 5, 0, 0, 0, 0, 0, 0}, 
    {9, 2, 1, 0, 0, 0, 0, 0, 0}, 
    {6, 4, 7, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 1, 2, 3, 0, 0, 0}, 
    {0, 0, 0, 7, 8, 4, 0, 0, 0}, 
    {0, 0, 0, 6, 9, 5, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 8, 7, 3}, 
    {0, 0, 0, 0, 0, 0, 9, 6, 2}, 
    {0, 0, 0, 0, 0, 0, 1, 4, 5}
  };
  
	if (SudokuSolution(board1, 0, 0)) cout << "\nBoard 1 Solution" << endl;
	Sudoku(board1);
  
	if (SudokuSolution(board2, 0, 0)) cout << "Board 2 Solution" << endl;
	Sudoku(board2);
  
  if (SudokuSolution(board3, 0, 0)) cout << "Board 3 Solution" << endl;
	Sudoku(board3);

  if (SudokuSolution(board4, 0, 0)) cout << "Board 4 Solution" << endl;
	Sudoku(board4);

	return 0;
}
//if the board inserted has no solution, it prints the board with the zeros still in it.