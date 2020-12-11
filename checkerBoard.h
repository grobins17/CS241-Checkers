/*
checkerBoard.h

Initializes the checkerBoard class

 */
#ifndef CHECKERBOARD_H //definition check for compilation safety
#define CHECKERBOARD_H
#include <stack>
#include<iostream>
#include "square.h"
#include "move.h"

using namespace std;

class CheckerBoard{ 
 public:

  CheckerBoard();
  //Constructor function

  void initBoard();
  //Initialize the Board as it should be

  void printBoard();
  //Print the board to the console

  void refreshBoard();
  //Iterates through each square, refreshing the visial.

  void printArray(int *arr, int current);
  //Prints given arrays
  
  int isCurrentEmpty(int current_row, int current_col);
  //checks if current space is empty

  void getLegalMoves(int current_row, int current_col);
  // return a (maybe list?) of possible moves from a square
  
  void move(int row, int col, int dest_row, int dest_col);
  //changes the Board and moves a Piece from one Square to another
 
  int canCapture(int current, int direction);
  // checks to see if a capture is possible. Adds to the array of possible moves
  
  void capture(int current_row, int current_col, int proposed_row, int proposed_col); 
  //used in the move method. If canCapture is true, then we call the capture method. It will be added as an if else statement
  stack<Move *> getSlides(int, int);

  stack<Move *> getJumps(int, int, int *, int, int, int);
  
 private:

  Square* board;//array of squares to act as the "board"
  int *blackLegal; // holds possible legal moves for black. Gave a possibility of 10 moves that could be done in one turn
  int *redLegal; // holds possible legal mores for red. Gave a possibility of 10 moves that could be done in one turn
  int *blackCapture; // holds possible legal captures for black. 
  int *redCapture; // holds possible legal captures for red. 
};
#endif
