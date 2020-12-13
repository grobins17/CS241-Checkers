#include<iostream>
#include "piece.h"

using namespace std;
    
Piece::Piece(){ //constructor (sets it to a red pawn)
  black = 0;
  king = 0;
}
int Piece::isKing(){ //returns king value
  return king;
}
int Piece::isBlack(){ //returns black value
  return black;
}
void Piece::promote(){ //changes the piece to a king
  king = 1;
}
void Piece::setColor(int isBlack){ //changes the color (for setup)
  black = isBlack;
}
