/*
checkerBoard.h

Initializes the checkerBoard class

 */
#ifndef CHECKERBOARD_H //definition check for compilation safety
#define CHECKERBOARD_H
#include <stack>
#include<iostream>
#include "move.h"
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
  
  WINDOW* getSqWin(int index);
  //Gets the window of the square at the index position of the board;

  void refreshBoard();
  //Iterates through each square, refreshing the visial.

  int isCurrentEmpty(int current_row, int current_col);
  //checks if current space is empty

  Move ** getLegalMoves(int current_row, int current_col);
  // return a (maybe list?) of possible moves from a square
  
  void move(int row, int col, Move * move);
  //changes the Board and moves a Piece from one Square to another
 
  stack<Move *> getSlides(int, int);

  stack<Move *> getJumps(int, int, int *, int, int, int);
  
 private:

  Square* board;//array of squares to act as the "board"
 };
#endif
