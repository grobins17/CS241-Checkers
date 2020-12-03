//Square.h

#ifndef SQUARE_H //compilation protections
#define SQUARE_H
#include<iostream>
#include "piece.h"

using namespace std;

class Square{
  //Values unless specified automatically are turned to private
  
  //row the square is located in the 2D array
  int row;
  
  //col the square is located in the 2D array
  int col;

  //pointer to a Piece it can contain

 public:

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

  //gets the color of the piece on the square
  
  //Sets the Piece to a pointer
  void setPiece(Piece * newPiece);

  //Removes the pointer to a Piece
  void removePiece();
};
#endif
