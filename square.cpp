//Square Class

#include<iostream>
#include "square.h"

using namespace std;


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
int Square::getCol(){
  return col;
}
void Square::setCol(int c){
  col = c;
}
int Square::getRow(){
  return row;
}
void Square::setRow(int r){
  row = r;
}
int Square::isEmpty(){
  return (ptr == NULL);
}
int Square::getColor(){
  return ptr->isBlack();
}
void Square::setPiece(Piece * newPiece){
  ptr = newPiece;
}
void Square::removePiece(){
  ptr = NULL;
}
