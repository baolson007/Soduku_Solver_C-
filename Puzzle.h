/*
Puzzle.h
Ben Olson
11-16-17

Header file for the Puzzle class. A Puzzle object consists of a 2D array of 
Square objects, each notably containing an integer value, among other attributes. 
The puzzle tracks and manages the position and content of square objects, so that the 
rules of solving a Sudoku puzzle are properly adhered to. Each 3x3 block must contain 
all digits 1-9, with no duplicates existing in the entire puzzle's row or column in that
position, as well as no duplicates existing within any given 3x3 block. A puzzle is 
solveable if those rules can be followed and all cells (Square objects)  can be filled
with a valid digit.
*///


#pragma once
#include <string>
#include <iostream>
#include "Square.h"
using namespace std;

const int MAX_ROW = 9;
const int MAX_COL = 9;

class Puzzle {

	// Attributes
	Square board[MAX_ROW][MAX_COL];
	int emptyCount; // how many are empty
	int puzzleSize; // fixed value, how many squares are variable

public:
	//default constructor
	Puzzle();

	//returns a const reference to the square at the location passed
	Square& get(int row, int col);

	//sets the value of a square at the given location
	//to the specified value. The legality of placement
	//is not of concern to this method. This is only
	//used for initialization/ reading in from the istream
	//at the beginning of program execution
	void setInitial(int row, int col, int value);

	/*
	sets the value of a square at the given location 
	to the specified value. If legal, set returns TRUE
	and updates the Square object’s ‘value’ field.
	*/
	bool set(int row, int col, int value);

	//used to check initial puzzle if there are any duplicates 
	//in the initialized values across rows or columns of the 
	//entire puzzle
	bool isLegal(int row, int col, int value);

	//to check if valid in row, need to assess all columns in that row
	//returns true if value can be placed in that row
	bool isLegalRow(int row, int value);

	//to check if valid in col, need to assess all rows in that col.
	//returns true if value can be placed in that col
	bool isLegalCol(int col, int value);

	//generates block ID for square object
	int createBlockID(int row, int col);

	//checks 3x3 block for duplicate values, returns true if 
	//value can be placed in the block
	bool checkBlock(int blockID, int row, int col, int value);

	//accessor for puzzle size. size = number of variable squares
	//at any given time
	int size();

	//increments puzzleSize
	void sizeIncrement();

	//returns puzzle size
	int getSize();

	//used for istream, returns number of empty cells while
	//initializing
	int numEmpty();

	//finds next available empty square on board
	void findEmpty(int& row, int& col);

};