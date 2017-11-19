/*
Puzzle.cpp
Ben Olson
11-16-17

Implentation of Puzzle class. Contains methods that enforce the rules for
solving Sudoku puzzle, as described in Puzzle.h; 
Note the use of 2 set____() methods; 1 method for initialized values, which 
may or may not be legal, and the other method is used for solving the puzzle and 
enforcing Sudoku rules.
*///

#include "Puzzle.h"
#include "Square.h"

//default constructor
Puzzle::Puzzle() {
	emptyCount = MAX_ROW * MAX_COL;
	puzzleSize = 0;
}

//returns a const reference to the square at the location passed
Square& Puzzle::get(int row, int col)
{
	return board[row][col];//
}

//sets the value of a square at the given location
//to the specified value. The legality of placement
//is not of concern to this method. This is only
//used for initialization/ reading in from the istream
//at the beginning of program execution
void Puzzle::setInitial(int row, int col, int value)
{
	board[row][col].setValue(value);
	emptyCount--; //if setting a sqaure, decrement empty count
	if (value != 0) {
		board[row][col].fixed = true;
	//	puzzleSize++; // tracks how many total squares can be variable
	}
	board[row][col].block = createBlockID(row, col);
}


/*
sets the value of a square at the given location
to the specified value. If legal, set returns TRUE
and updates the Square object’s ‘value’ field.
*/
bool Puzzle::set(int row, int col, int value)
{
	int blockID = createBlockID(row, col);
	board[row][col].setBlock(blockID); 

	
	if (value == 0) {
		board[row][col].setValue(value);
		puzzleSize++;
		return true;
	}

	if (isLegalRow(row, value) && isLegalCol(col, value) &&
		checkBlock(blockID, row, col, value)) 
	{
		board[row][col].setValue(value);
		puzzleSize--;
		return true;
	}
	return false;
}

//used to check initial puzzle if there are any duplicates 
//in the initialized values across rows or columns of the 
//entire puzzle
bool Puzzle::isLegal(int row, int col, int value)
{
	if (value == 0)
		return true;
	bool legal = false;
	bool rowLegal = false;
	bool colLegal = false;

	int valueCountRow = 0;

	//to check if valid in row, need to assess all columns in that row
	for (int k = 0; k < MAX_COL; k++) {
		if (board[row][k].getValue() == value) { // if value already exists in row, increment valueCount
			valueCountRow++;
			if (valueCountRow > 1)
				return false;
		}
		else {
			rowLegal = true;
		}
	}
	int valueCountCol = 0;

	//to check if valid in col, need to assess all rows in that col
		for (int i = 0; i < MAX_ROW; i++) {
			if (board[i][col].getValue() == value) { // if value already exists in row, increment value count
				valueCountCol++;
				if (valueCountCol > 1) // if more than one square contain the value passed in, return false
					return false;
			}
			else {
				colLegal = true;
			}
		}

	//If both row and col are legal, the value is legal
	if (rowLegal == true && colLegal == true)
		legal = true;

	//legal is false by default.
	return legal;
}


//to check if valid in row, need to assess all columns in that row
//returns true if value can be placed in that row
bool Puzzle::isLegalRow(int row, int value) {
	for (int k = 0; k < MAX_COL; k++) {
		if (board[row][k].getValue() == value) { 
				return false;
		}
	}
	return true;
}

//to check if valid in col, need to assess all rows in that col.
//returns true if value can be placed in that col
bool Puzzle::isLegalCol(int col, int value) {
	for (int k = 0; k < MAX_ROW; k++) {
		if (board[k][col].getValue() == value) {
			return false;
		}
	}
	return true;
}

//generates block ID for square object
int Puzzle::createBlockID(int row, int col)
{
	int rowID = -1;
	int colID = -1;
	int blockID = -1;

	//Row assignment for blockID
	if (row == 0 ||row == 1 || row == 2)
		rowID = 1;
	else if (row == 3 ||row ==4 || row ==5)
		rowID = 2;
	else if (row == 6 ||row ==7  || row == 8)
		rowID = 3;

	//Col assignment for blockID
	if (col == 0 || col == 1 || col == 2)
		colID = 1;
	else if (col == 3 || col == 4 || col == 5)
		colID = 2;
	else if (col == 6 || col ==7 || col ==8)
		colID = 3;

	//blockID assignment
	if(rowID == 1){
		if (colID == 1){
			blockID = 1;
		}else if(colID == 2){
			blockID = 2;
		}else
			blockID = 3;
	} //end rowID 1

	else if(rowID == 2){
		if (colID == 1){
			blockID = 4;
		}else if(colID == 2){
			blockID = 5;
		}else
			blockID = 6;
	} //end rowID 2

	else if(rowID == 3){
		if (colID == 1){
			blockID = 7;
		}else if(colID == 2){
			blockID = 8;
		}else
			blockID = 9;
	} //end rowID 3

	return blockID;
}

//checks 3x3 block for duplicate values, returns true if 
//value can be placed in the block
bool Puzzle::checkBlock(int blockID, int row, int col, int value)
{
	bool noDuplicates = false;
	/* determine block, start at begining of block
	for-loop over row then col, if value already exists in block,
	noDuplicates == false*/

	int startRow = -1;
	int startCol = -1;

	if (blockID == 1) {
		startRow = 0;
		startCol = 0;
	}
	else if (blockID == 2) {
		startRow = 0;
		startCol = 3;
	}
	else if (blockID == 3) {
		startRow = 0;
		startCol = 6;
	}
	else if (blockID == 4) {
		startRow = 3;
		startCol = 0;
	}
	else if (blockID == 5) {
		startRow = 3;
		startCol = 3;
	}
	else if (blockID == 6) {
		startRow = 3;
		startCol = 6;
	}
	else if (blockID == 7) {
		startRow = 6;
		startCol = 0;
	}
	else if (blockID == 8) {
		startRow = 6;
		startCol = 3;
	}
	else if (blockID == 9) {
		startRow = 6;
		startCol = 6;
	}

	
	//copy contents of block into array, check array for duplicates
	int blockArray[9];
	int arrayCount = 0;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			Square temp = board[startRow][startCol];
			int tempValue = temp.getValue();
			if (startRow == row && startCol == col) {
				blockArray[arrayCount] = 0;//value already exists in it's designated position. this is a workaround
			}
			else {
				blockArray[arrayCount] = tempValue;
			}
			startCol++;
			arrayCount++;
		}
		startRow++;
		startCol -= 3;//reset col to original startCol value
	}

	//search array for duplicate of value
	for (int i = 0; i < 9; i++) {
		if (blockArray[i] == value && value != 0) {
			noDuplicates = false;
			return noDuplicates;
		}
		else
			noDuplicates = true;
	}
	return noDuplicates;
}

//accessor for puzzle size. size = number of variable squares
//at any given time
int Puzzle::size()
{
	return puzzleSize;
}

//increments puzzleSize
void Puzzle::sizeIncrement()
{
	puzzleSize++;
}

//returns puzzle size
int Puzzle::getSize()
{
	return puzzleSize;
}

//used for istream, returns number of empty cells while
//initializing
int Puzzle::numEmpty()
{
	return emptyCount;
}

//finds next available empty square on board
void Puzzle::findEmpty(int & row, int & col)
{
	for (int i = row; i < MAX_ROW; i++) {
		for (int j = 0; j < MAX_COL; j++) {
			if (this->get(i, j).getValue() == 0) {
				row = i;
				col = j;
				return;
			}
		}
	}
}


