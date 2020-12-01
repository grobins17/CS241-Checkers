#include<iostream>
#include "piece.h"

using namespace std;

Piece::Piece(int isKing, int isBlack){
  black = isBlack;
  king = isKing;
}
int Piece::isKing(){
  return king;
}
int Piece::isBlack(){
  return black;
}
