#include<iostream>
#include "piece.h"

using namespace std;

Piece::Piece(int isBlack){
  black = isBlack;
  king = 0;
}
int Piece::isKing(){
  return king;
}
int Piece::isBlack(){
  return black;
}
void Piece::promote(){
  king = 1;
}
