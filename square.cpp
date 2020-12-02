//Square Class

#include<iostream>
#include "square.h"

using namespace std;

// constructor for the Square object
Square::Square (int a, int b, int c, Piece *ptr){
	row = a;
	col = b;
	type = c;
	piece = ptr;
}
int Square::getCol(){
  return col;
}
int Square::getRow(){
  return row;
}
int Square::getType(){
  return type;
}
void Square::setPiece(Piece * newPiece){
  piece = newPiece;
}
void Square::removePiece(){
  piece = NULL;
}
