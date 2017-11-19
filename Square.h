/*
Square.h
Ben Olson
11-16-17

Header file for the Square class. Square objects will be used
to fill a Puzzle object, which will store a 2D array of Square objects
that wil represent a Sudoku puzzle. Each square will represent any
given cell within the 9x9 sudoku puzzle. Puzzle will be declared as a 
friend class to Square, so that it can access Square's protected 
setValue(int value) method.
*/

#pragma once
#include <iostream>
#include <string>

using namespace std;

class Puzzle;

class Square {

	//attributes
	int value = -1;
	bool fixed = false;
	int squareRow;
	int squareCol;
	int block;

	friend class Puzzle;

protected:
	//setValue is protected so that it's contents 
	//may not be inadvertently modified during recursion.
	//Puzzle is declared as a friend so that Puzzle can
	//change the value of a Square object. 
	void setValue(int);

public:

	//default constructor
	Square();

	//parameterized constructor
	Square(int row, int col, int value);

	//returns value of square object
	int getValue();

	//returns status of square.
	//if False, the square's value is 
	//variable and it can be changed.
	//if true, the value was originally
	//read in from the istream
	bool getFixed();

	//sets the block ID for the sudoku grid system.
	//blocks are 9 (3x3) squares with IDs as follows:
	// 1 2 3
	// 4 5 6
	// 7 8 9
	void setBlock(int id);

	//returns block ID
	int getBlock();
};//