#include<iostream>
#include<stdlib.h>
#include<string>
#include "checkerBoard.h"

using namespace std;

CheckerBoard::CheckerBoard(){ //constructor
  Square* arr = new Square[64]; //make the board (now a one-dimensional array of Squares)

  
  for(int i = 0; i < 64; i++){
    arr[i] = Square(i/8,i%8 , NULL); //initialize all the squares in the board with the row, the row, and an empty pointer to a Piece object.
  }
  board = arr; //change the class attribute
}
void CheckerBoard::initBoard(){ //initialize the board
  for(int i = 0; i < 64; i++){ //for each Square in the checkerBoard
    if((i % 8 + i/8)%2 == 1){ //if the Square isn't supposed to be empty at the start
      Piece newPiece(0, 0); //make a new Piece
      board[i].setPiece(&newPiece); //change the pointer of the Square to point at the new Piece
    }
    else{ //else, set the Square's coordinates and leave it empty
      board[i].setRow(i/8);
      board[i].setCol(i%8);
    }
  }
}

void CheckerBoard::printBoard(){ //debug function to print the board. 
  for(int i = 0; i < 64; i++){
    if(board[i].isEmpty()){ //if the Square is empty, print an "[ ]"
      cout << "[ ]";
    }else{//if not empty, print an "[x]"
      cout << "[x]";
    }if(i%8 == 7){
      cout << endl;
    }
  }
}


