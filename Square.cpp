/*
Square.cpp
Ben Olson
11-16-17
//
Implementation of the Square class, mainly consists of 
accessor and mutator methods to manipulate/return Square state. 
*/

#include "Square.h"
#include "Puzzle.h"

class Puzzle;

//default constructor
Square::Square() {
	//values initialized in header file
}

//parameterized constructor
Square::Square(int row, int col, int digit)
{
	squareRow = row;
	squareCol = col;
	value = digit;
}

//setValue is protected so that it's contents 
//may not be inadvertently modified during recursion.
//Puzzle is declared as a friend so that Puzzle can
//change the value of a Square object.
void Square::setValue(int n)
{
	value = n;
}

//returns value of square object
int Square::getValue()
{	
	return value;
}

//returns status of square.
//if False, the square's value is 
//variable and it can be changed.
//if true, the value was originally
//read in from the istream
bool Square::getFixed()
{
	return fixed;
}

//sets the block ID for the sudoku grid system.
//blocks are 9 (3x3) squares with IDs as follows:
// 1 2 3
// 4 5 6
// 7 8 9
void Square::setBlock(int id)
{
	block = id;
}

//returns block ID
int Square::getBlock() {
	return block;
}
