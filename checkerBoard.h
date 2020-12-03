/*
checkerBoard.h

Initializes the checkerBoard class

 */
#ifndef CHECKERBOARD_H //definition check for compilation safety
#define CHECKERBOARD_H

#include<iostream>
#include "square.h"

using namespace std;

class CheckerBoard{ 
 public:

  CheckerBoard();
  //Constructor function

  void initBoard();
  //Initialize the Board as it should be

  void printBoard();
  //Print the board to the console
  void getLegalMoves(int, int);
  
  void move(int row, int col, int dest_row, int dest_col);
  
private:

  Square* board;
  //array of squares to act as the "board"
};
#endif
