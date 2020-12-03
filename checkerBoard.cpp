#include<iostream>
#include<stdlib.h>
#include<string>
#include "checkerBoard.h"

using namespace std;

CheckerBoard::CheckerBoard(){ //constructor
  Square* arr = new Square[64]; //make the board (now a one-dimensional array of Squares)
  for(int i = 0; i < 64; i++){
    arr[i] = Square(i/8,i%8, NULL); //initialize all the Squares in the board
  }
  board = arr; //change the checkerBoard attribute to point at initialized array
}

void CheckerBoard::initBoard(){ //initialize the board
  for(int i = 0; i < 64; i++){ //for each Square in the checkerBoard
    if((i/8 + i%8)%2 == 1){ //if the Square isn't supposed to be empty at the start
      
      //for the top squares of checkers
      if(i/8 <= 2){ 
	Piece *a = new Piece(); //make a new black Piece and add it to the board
	a->setColor(1);
	board[i].setPiece(a);
      }

      //for the bottow rows of checkers
      else if (i/8 >= 5){ 
	Piece *b = new Piece(); //make a new red Piece and add it to the board
	b->setColor(0);
	board[i].setPiece(b);
      }
    }
  }
}

void CheckerBoard::printBoard(){ //debug function to print the board. 
  for(int i = 0; i < 64; i++){

    if(board[i].isEmpty()){ //if the Square is empty, print an "[ ]"
      cout << "[ ]";
    }else if((*board[i].ptr).isBlack() == 0){
      cout << "[x]";
    }else{
      cout << "[o]";
    }

    if(i%8 == 7){
      cout << endl;
    }
  }
}


