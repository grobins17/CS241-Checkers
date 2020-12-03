//Square Class

#include<iostream>
#include "square.h"

using namespace std;

//unparameterized constructor (for setup)
Square::Square(){ 
  row = 0;
  col = 0;
  ptr = NULL;
}
// constructor for the Square object
Square::Square (int a, int b, Piece *piece){
	row = a;
	col = b;
	ptr = piece;
}
int Square::getCol(){ //returns column
  return col;
}
void Square::setCol(int c){ //sets column
  col = c;
}
int Square::getRow(){ //returns row
  return row;
}
void Square::setRow(int r){//sets row
  row = r;
}
int Square::isEmpty(){ //returns true if no pointer to a Piece is in the square
  return (ptr == NULL);
}
void Square::setPiece(Piece * newPiece){ //changes the pointer to a Piece in the square
  ptr = newPiece;
}
void Square::removePiece(){ //removes the pointer to the Piece
  ptr = NULL;
}
