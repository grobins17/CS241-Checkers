#include<iostream>
#include<string>
#include "checkerBoard.h"

using namespace std;
checkerBoard::checkerBoard(){
  Piece board[8][8];
}
void checkerBoard::initBoard(){
  for(int row = 0; row < 8; row++){
    for(int col = 0; col < 8; col++){
      if(((row+col) % 2) == 1){
	Piece newPiece(0, 0);
	Square newSquare(row, col, 1);
	newSquare.setPiece(&newPiece);
	board[row][col] = newSquare;
      }
      else{
	Square emptySquare(row, col, 0);
	board[row][col] = emptySquare;
      }
    }
  }
}
void checkerBoard::printBoard(){
  for(int y = 0; y < 8; y++){
    for(int x = 0; x < 8; x++){
      cout << board[y][x];
    }
  }
}

