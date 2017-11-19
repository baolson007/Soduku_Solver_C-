/*
Prog3.cpp "Main"
Ben Olson
11-6-17
//
This is the driver for the Sudoku solver program. It contains operator
overloads for the istream and ostream. It also contains a recursive backtracking
'solve' method that takes a Puzzle object and returns either TRUE or FALSE. 
The user will input a sudoku puzzle as a stream of 81 digits. The puzzle will then be
displayed, and an attempt to solve the puzzle will either yield a displayed solved puzzle
or a message indicating that the puzzle could not be solved. 
*/

#pragma once
#include "Puzzle.h"
#include "Square.h"
#include <iostream>
#include <string>
#include <cctype>

using namespace std;


/*
overloaded cin >> operator to read digits as characters in to 
a puzzle object. 
*/
istream& operator >> (istream& in, Puzzle& p)
{
	//char c;
	bool fixedValue;
	while (p.numEmpty() != 0) {
		for (int i = 0; i < MAX_ROW; i++) {
			for (int j = 0; j < MAX_COL; j++) {
				char c='-';
				while (!isdigit(c)) {
					c = in.get(); //ASSUMING ONLY INTEGER INPUT FOR NOW
				}
					int digit = c - 48; //to undo ASCII conversion
					if (digit == 0) {
						p.sizeIncrement();
						fixedValue = false;
					}
					else {
						fixedValue = true;
					}
					p.setInitial(i, j, digit);
				continue;
			}//end inner For
		}//end outer For
	}//end while
	return in;
}

/*
cout overload in order to properly display Puzzle
objects in a "human friendly" manner. 
*/
ostream & operator << (ostream & os, Puzzle & p)
{
	os << '+';
	for (int i = 0; i < ((2 * MAX_COL + 1) + (MAX_COL / 3 + 1)); i++)//THIS WORKS FOR A 9*9 
		os << '-';
	os << '+';

	for (int i = 0; i < MAX_ROW; i++) {
		os << endl;
		os << '|' << ' ';
		for (int j = 0; j < MAX_COL; j++) {
			Square temp = p.get(i, j);
			if (temp.getValue() == 0)
				os << ' ' << ' ';
			else {
				os << temp.getValue() << ' ';
			}
			if ((j + 1) % 3 == 0) {
				os << '|' << ' ';
			}
		}//end for COL
		os << endl;
		if ((i + 1) % 3 == 0) {
			os << '+';
			for (int i = 0; i < ((2 * MAX_COL + 1) + (MAX_COL / 3 + 1)); i++) //THIS WORKS FOR A 3*3
				os << '-';
			os << '+' << endl;
		}
	}// end for ROW

	return os;
}


//solve method uses '&' to update my row and col 
//parameters to find the next empty square during
//the recursive calls. Recursion continues until the
//number of (valid) empty squares is equal to zero.
bool solve(Puzzle& p, int row, int col)
{
	//BASE CASE
	if (p.getSize() == 0) {
		return true;
	}

	//updates row/col to next empty position in puzzle using &
	p.findEmpty(row, col);

	//RECURSIVE CALL
	for (int digit = 1; digit <= 9; digit++) {//try each digit
		if (p.set(row, col, digit)) { // if valid
			if (solve(p, row, col)) { // try next
				return true;
			}
			else {
				p.set(row, col, 0); //delete invalid digit
			}
		}//end if
	}//end for
	return false;
}

int main() {

	Puzzle p;
	cin >> p;
	cout << p;
	
	if(solve( p, 0, 0)){//puzzle can be solved
		cout << p; //display solved puzzle
	}
	else{
		cout << "Could not solve puzzle." << endl;
	}
}


