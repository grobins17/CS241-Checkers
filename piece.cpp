#include<iostream>
#include "piece.h"

using namespace std;

Piece::Piece(){ //constructor (sets it to a red pawn)
  black = 0;
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
void Piece::setColor(int isBlack){
  black = isBlack;
}
