#ifndef PIECE_H //compilation protections 
#define PIECE_H
#include<iostream>

using namespace std;

class Piece{
  //0 for red, 1 for black
  int black;

  //0 for regular piece, 1 for king piece
  int king;

 public:
  Piece();  
  //constructor

  //method for getting the color of the piece 
  int isBlack();

  //method for getting the type of the piece
  int isKing();

  //method for changing the king variable
  void promote();

  //method for changing the color of the piece (for setup)
  void setColor(int);
  
};
#endif
