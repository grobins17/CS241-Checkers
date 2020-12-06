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
  for(int i = 0; i < 8; i++){ //numbers for convenience
    cout << "  " <<i;
  }
  cout << endl;
  cout << 0;
  for(int i = 0; i < 64; i++){
    if(board[i].isEmpty()){ //if the Square is empty, print an "[ ]"
      cout << "[ ]";
    }else if((*board[i].ptr).isBlack()){ //if the Piece in the square is black, print "[B]"
      cout << "[B]";
    }else{ //if the Piece in the square is red, print "[R]"
      cout << "[R]";
    }

    if(i%8 == 7){
      cout << endl;
      if((i+1)/8 != 8){
	cout << (i+1)/8;
      }
    }
  }
}
void CheckerBoard::getLegalMoves(int current_row, int current_col){ 
  int current = 8*current_row + current_col; //current index in the board
  int upperLeftDiagonal = current - 9;
  int upperRightDiagonal = current -7;
  int lowerRightDiagonal = current + 9;
  int lowerLeftDiagonal = current +7;
  cout << "Possible moves: \n";
  Piece cur_piece = *(board[current].ptr);  //current Piece 
  if(cur_piece.isKing()){ //checks if piece is king or not
    if(cur_piece.isBlack()){ //checks is the piece is black(user's piece)
      ;
    }else{
      ;
    }
  }
  else{ //not a king
    if(cur_piece.isBlack()){ //checks is the piece is black
      if(current%8 == 0){//checks if the piece is on the left wall of board
	if(board[lowerRightDiagonal].isEmpty()){//checks if left diagonal is empty
          cout << "Row: " << current/8 + 1<< " " << "Col: " << lowerRightDiagonal%8 << "\n"; // prints coordinates       
        }else{
	  cout << "Sorry, there are no legal moves :(";
	}
      }else if(current%8 ==7){ //checks if the piece is on the right wall 
	if(board[lowerLeftDiagonal].isEmpty()){//checks if left diagonal is empty
          cout << "Row: " << current/8 + 1<< " " << "Col: " << lowerLeftDiagonal%8 << "\n"; // prints coordinates       
        }else{
	  cout << "Sorry, there are no legal moves :(";
        } 
      }else{
	if(board[lowerLeftDiagonal].isEmpty() && board[lowerRightDiagonal].isEmpty()){
	  cout << "Row: " << current/8 + 1<< " " << "Col: " << lowerLeftDiagonal%8 << "\n"; // prints coordinates
	  cout << "Row: " << current/8 + 1<< " " << "Col: " << lowerRightDiagonal%8 << "\n"; // prints coordinates       
	}
	else if(!board[lowerRightDiagonal].isEmpty() && board[lowerLeftDiagonal].isEmpty()){
	  cout << "Row: " << current/8 + 1<< " " << "Col: " << lowerLeftDiagonal%8 << "\n"; // prints coordinates
	}
	else if(!board[lowerLeftDiagonal].isEmpty() && board[lowerRightDiagonal].isEmpty()){
	  cout << "Row: " << current/8 + 1<< " " << "Col: " << lowerRightDiagonal%8 << "\n"; // prints coordinates 
	}
	else{
	  cout << "Sorry, there are no legal moves :(";
	}
      }
    }else{
      if(current%8 == 0){//checks if the piece is on the left wall of board
	 if(board[upperRightDiagonal].isEmpty()){//checks if right diagonal is empty
          cout << "Row: " << current/8 - 1<< " " << "Col: " << upperRightDiagonal%8 << "\n"; // prints coordinates       
        }else{
	  cout << "Sorry, there are no legal moves :(";
	}
       }else if(current%8 ==7){
	 if(board[upperLeftDiagonal].isEmpty()){//checks if left diagonal is empty
          cout << "Row: " << current/8 - 1<< " " << "Col: " << upperLeftDiagonal%8 << "\n"; // prints coordinates       
        }else{
	  cout << "Sorry, there are no legal moves :(";
        } 
       }else{
	 if(board[upperLeftDiagonal].isEmpty() && board[upperRightDiagonal].isEmpty()){
	   cout << "Row: " << current/8 - 1<< " " << "Col: " << upperLeftDiagonal%8 << "\n"; // prints coordinates
	   cout << "Row: " << current/8 - 1<< " " << "Col: " << upperRightDiagonal%8 << "\n"; // prints coordinates 
	 }
	 else if(!board[upperRightDiagonal].isEmpty() && board[upperLeftDiagonal].isEmpty()){
	   cout << "Row: " << current/8 - 1<< " " << "Col: " << upperLeftDiagonal%8 << "\n"; // prints coordinates
	 }
	 else if(!board[upperLeftDiagonal].isEmpty() && board[upperRightDiagonal].isEmpty()){
	   cout << "Row: " << current/8 - 1<< " " << "Col: " << upperRightDiagonal%8 << "\n"; // prints coordinates 
	 }
	 else{
	   cout << "Sorry, there are no legal moves :(";
	 }
      }
    }
  }  
  cout << "\n";
}

void CheckerBoard::move(int current_row, int current_col, int proposed_row, int proposed_col){ //move function
  int current = 8*current_row + current_col; //current index in the Board
  int proposed = 8*proposed_row + proposed_col; //proposed index in the Board
  if(board[current].isEmpty() || (!(board[proposed].isEmpty())) || (proposed_row + proposed_col)%2 == 0){ //if the proposal is bad print an error message (not complete)
    cout << "that's no good!";
  }
  else{ //otherwise move the Piece to the proposed spot and remove it from the old Square
    board[proposed].setPiece(board[current].ptr);
    board[current].removePiece();
  }
}
