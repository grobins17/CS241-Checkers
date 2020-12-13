//Square.h

#ifndef SQUARE_H //compilation protections
#define SQUARE_H
#include<iostream>
#include "piece.h"
#include <ncurses.h>

using namespace std;

class Square{
  //Values unless specified automatically are turned to private
  
  //row the square is located in the 2D array
  int row;
  
  //col the square is located in the 2D array
  int col;

  //window object is for GUI
  WINDOW *window;

 public:

  //pointer to a Piece it can contain  
  Piece *ptr;

  //Unparameterized constructor
  Square();

  //Parameterized constructor 
  Square(int, int, Piece*);	
  
  //gets row 
  int getRow();

  //sets row to r
  void setRow(int r);

  //gets col
  int getCol();

  //sets col to c
  void setCol(int c);
      
  //Checks if the Square contains a Piece
  int isEmpty();
  
  //Sets the Piece to a pointer
  void setPiece(Piece * newPiece);

  //Removes the pointer to a Piece
  void removePiece();

  //GUI COMPONENTS
  void initWindow();
  //initializes the windows for each square
  
  WINDOW * getWindow();
  //gets the window of a square

  void sqrefresh();
  // refreshes the square

  void highlight();
  //Highlights the square in a cyan color
};
#endif
