#include<iostream>
#include<stdlib.h>
#include<string>
#include "checkerBoard.h"

using namespace std;

CheckerBoard::CheckerBoard(){ //constructor
  numRed = 12;
  numBlack = 12;
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

Square CheckerBoard::getSquare(int row, int col){
  int index = (row*8) + col;
  return board[index];
}

void CheckerBoard::refreshBoard(){
  for(int i=0; i<64; i++){
    	board[i].sqrefresh();
  }
}

int CheckerBoard::isCurrentEmpty(int current_row, int current_col){
  return board[8*current_row + current_col].isEmpty();
}

stack<Move *> CheckerBoard::getSlides(int current_row, int current_col){
  std::stack<Move *> stck;
  int current = 8*current_row + current_col; //current index in the board
  int upperLeftDiagonal = current - 9;
  int upperRightDiagonal = current -7;
  int lowerRightDiagonal = current + 9;
  int lowerLeftDiagonal = current +7;
  Piece cur_piece = *(board[current].ptr);  //current Piece 
  if(cur_piece.isKing()){ //if piece is a king
    if(current == 7){ //king in upper right corner
      if(board[lowerLeftDiagonal].isEmpty()){
	  int ptr[12] =  {};
	  Move *thisMove = new Move(lowerLeftDiagonal, ptr);
	  stck.push(thisMove);
	}
      
    }else if(current == 56){ //king in lower left corner
      if(board[upperRightDiagonal].isEmpty()){
	  int ptr[12] =  {};
	  Move *thisMove = new Move(upperRightDiagonal, ptr); 
	  stck.push(thisMove);
	}
      
    }else if (current%8 == 0){ //king on left wall
      if(board[lowerRightDiagonal].isEmpty()){
	int ptr[12] =  {};
	Move *thisMove = new Move(lowerRightDiagonal, ptr);
	stck.push(thisMove);
      }
      if(board[upperRightDiagonal].isEmpty()){
	int ptr[12] =  {};
	Move *thisMove = new Move(upperRightDiagonal, ptr); //Lower right
	stck.push(thisMove);
      }
      
    }else if (current%8 == 7){ //king on right wall
      if(board[lowerLeftDiagonal].isEmpty()){
	int ptr[12] =  {};
	Move *thisMove = new Move(lowerLeftDiagonal, ptr);
	stck.push(thisMove);
      }
      if(board[upperLeftDiagonal].isEmpty()){
	int ptr[12] =  {};
	Move *thisMove = new Move(upperLeftDiagonal, ptr);
	stck.push(thisMove);
      }
      
    }else if (current/8 == 0){ //king on top row
      if(board[lowerLeftDiagonal].isEmpty()){
	int ptr[12] =  {};
	Move *thisMove = new Move(lowerLeftDiagonal, ptr);
	stck.push(thisMove);
      }if(board[lowerRightDiagonal].isEmpty()){
	int ptr[12] =  {};
	Move *thisMove = new Move(lowerRightDiagonal, ptr);
	stck.push(thisMove);
      }
      
    }else if(current/8 == 7){ //king on bottom row
      if(board[upperLeftDiagonal].isEmpty()){
	int ptr[12] =  {};
	Move *thisMove = new Move(upperLeftDiagonal, ptr);
	stck.push(thisMove);
      }if(board[upperRightDiagonal].isEmpty()){
	int ptr[12] =  {};
	Move *thisMove = new Move(upperRightDiagonal, ptr);
	stck.push(thisMove);
      }
     
    }else{ //king is in the middle of the board 
      if(board[upperLeftDiagonal].isEmpty()){
	int ptr[12] =  {};
	Move *thisMove = new Move(upperLeftDiagonal, ptr);
	stck.push(thisMove);
      }if(board[upperRightDiagonal].isEmpty()){
	int ptr[12] =  {};
	Move *thisMove = new Move(upperRightDiagonal, ptr);
	stck.push(thisMove);
      }if(board[lowerLeftDiagonal].isEmpty()){
	int ptr[12] =  {};
	Move *thisMove = new Move(lowerLeftDiagonal, ptr);
	stck.push(thisMove);
      }if(board[lowerRightDiagonal].isEmpty()){
	int ptr[12] =  {};
	Move *thisMove = new Move(lowerRightDiagonal, ptr);
	stck.push(thisMove);
      }
    }
  }else{ //piece is not a king
    if(cur_piece.isBlack()){ //if it's a black piece
      if(current%8 == 0){ //if it's on the left wall
	if(board[lowerRightDiagonal].isEmpty()){ //if the spot is empty
	  int ptr[12] =  {};
	  Move *thisMove = new Move(lowerRightDiagonal, ptr); //add the new move to the stack
	  stck.push(thisMove);
	}
      }else if(current%8==7){ //if the black piece is on the right wall
	if(board[lowerLeftDiagonal].isEmpty()){
	  int ptr[12] =  {};
	  Move *thisMove = new Move(lowerLeftDiagonal, ptr);
	  stck.push(thisMove);
	}
      }else{ //if the black piece is in the middle
	if(board[lowerRightDiagonal].isEmpty()){
	  int ptr[12] =  {};
	  Move *thisMove = new Move(lowerRightDiagonal, ptr); //Lower right
	  stck.push(thisMove);
	}
	if(board[lowerLeftDiagonal].isEmpty()){ 
	  int ptr[12] =  {};
	  Move *thisMove = new Move(lowerLeftDiagonal, ptr);
	  stck.push(thisMove);
	}
      }
    }else{ //if the piece is red
      if(current%8 == 0){  //if the regular red piece is on the left wall
	if(board[upperRightDiagonal].isEmpty()){
	  int ptr[12] =  {};
	  Move *thisMove = new Move(upperRightDiagonal, ptr); 
	  stck.push(thisMove);
	}
      }else if(current%8==7){ //if the regular red piece is on the right wall
	if(board[upperLeftDiagonal].isEmpty()){
	  int ptr[12] =  {};
	  Move *thisMove = new Move(upperLeftDiagonal, ptr);
	  stck.push(thisMove);
	}
      }else{ //if the regular reg piece is in the middle of the board
	if(board[upperRightDiagonal].isEmpty()){
	  int ptr[12] =  {};
	  Move *thisMove = new Move(upperRightDiagonal, ptr); 
	  stck.push(thisMove);
	}
	if(board[upperLeftDiagonal].isEmpty()){
	 int ptr[12] =  {};
	  Move *thisMove = new Move(upperLeftDiagonal, ptr);
	  stck.push(thisMove);
	}
      }
    }
  }
  return stck;
}
stack<Move *> CheckerBoard::getJumps(int current_row, int current_col, int caps[12], int index, int isBlack, int isKing){ //TODO: check that we're not backtracking
  stack<Move *> stack;
  int current = 8*current_row + current_col; //current index in the board  
  int ULD = current - 9;
  int URD = current -7;
  int LRD = current + 9;
  int LLD = current +7;  
  int UULD = current - 18;
  int UURD = current -14;   
  int LLRD = current + 18;
  int LLLD = current +14;

  int *newarr = new int[12];
  std::copy(caps, caps+12, newarr);
  //int ULD_captured = std::find(caps, caps + 12,  ULD) != caps+12;
  //int URD_captured = std::find(caps, caps + 12,  URD) != caps+12;
  //int LLD_captured = std::find(caps, caps + 12,  LLD) != caps+12;
  //int LRD_captured = std::find(caps, caps + 12,  LRD) != caps+12;

  if(isKing){ //if piece is a king (moves are the same b/w red and black the only difference is what they can capture)
    if(current_row < 2 || current_col < 2){ //upper left corner
      if(!board[LRD].isEmpty() && (board[LRD].ptr)->isBlack()-isBlack != 0 && board[LLRD].isEmpty()){
	newarr[index] = LRD;
	Move *newmove = new Move(LLRD, newarr);
	stack.push(newmove);
      }
    }else if(current_row < 2 || current_col > 5){ //upper right corner
      if(!board[LLD].isEmpty() && (board[LLD].ptr)->isBlack()-isBlack != 0 && board[LLLD].isEmpty()){
	newarr[index] = LLD;
	Move *newmove = new Move(LLLD, newarr);
	stack.push(newmove);
      }
    }else if(current_row >5 || current_col < 2){ //lower left corner
      if(!board[URD].isEmpty() && (board[URD].ptr)->isBlack() -isBlack != 0 && board[UURD].isEmpty()){
	newarr[index] = URD;
	Move *newmove = new Move(UURD, newarr);
	stack.push(newmove);
      }
    }else if(current_row > 5 || current_col > 5){ //lower right corner
      if(!board[ULD].isEmpty() && (board[ULD].ptr)->isBlack()-isBlack != 0 && board[UULD].isEmpty()){
	newarr[index] = ULD;
	Move *newmove = new Move(UULD, newarr);
	stack.push(newmove);
      }
    }else if(current_row <2){ //uppper two rows
      if(!board[LRD].isEmpty() && (board[LRD].ptr)->isBlack()-isBlack != 0 && board[LLRD].isEmpty()){
	newarr[index] = LRD;
	Move *newmove = new Move(LLRD, newarr);
	stack.push(newmove);
      }if(!board[LLD].isEmpty() && (board[LLD].ptr)->isBlack()-isBlack != 0 && board[LLLD].isEmpty()){
	newarr[index] = LLD;
	Move *newmove = new Move(LLLD, newarr);
	stack.push(newmove);
      }
    }else if (current_row > 5){ //lower two rows 
      if(!board[URD].isEmpty() && (board[URD].ptr)->isBlack() -isBlack != 0 && board[UURD].isEmpty()){
	newarr[index] = URD;
	Move *newmove = new Move(UURD, newarr);
	stack.push(newmove);
      }if(!board[ULD].isEmpty() && (board[ULD].ptr)->isBlack()-isBlack != 0 && board[UULD].isEmpty()){
	newarr[index] = ULD;
	Move *newmove = new Move(UULD, newarr);
	stack.push(newmove);
      }
    }else if (current_col < 2){ //leftmost two columns
      if(!board[URD].isEmpty() && (board[URD].ptr)->isBlack() -isBlack != 0 && board[UURD].isEmpty()){
	newarr[index] = URD;
	Move *newmove = new Move(UURD, newarr);
	stack.push(newmove);
      }if(!board[LRD].isEmpty() && (board[LRD].ptr)->isBlack()-isBlack != 0 && board[LLRD].isEmpty()){
	newarr[index] = LRD;
	Move *newmove = new Move(LLRD, newarr);
	stack.push(newmove);
      }
    }else if (current_col > 5){ //rightmost two columns
      if(!board[ULD].isEmpty() && (board[ULD].ptr)->isBlack()-isBlack != 0 && board[UULD].isEmpty()){
	newarr[index] = ULD;
	Move *newmove = new Move(UULD, newarr);
	stack.push(newmove);
      }if(!board[LLD].isEmpty() && (board[LLD].ptr)->isBlack()-isBlack != 0 && board[LLLD].isEmpty()){
	newarr[index] = LLD;
	Move *newmove = new Move(LLLD, newarr);
	stack.push(newmove);
      }
    }else{ //middle of the board
      if(!board[ULD].isEmpty() && (board[ULD].ptr)->isBlack()-isBlack != 0 && board[UULD].isEmpty()){
	newarr[index] = ULD;
	Move *newmove = new Move(UULD, newarr);
	stack.push(newmove);
      }if(!board[LLD].isEmpty() && (board[LLD].ptr)->isBlack()-isBlack != 0 && board[LLLD].isEmpty()){
	newarr[index] = LLD;
	Move *newmove = new Move(LLLD, newarr);
	stack.push(newmove);
      }if(!board[URD].isEmpty() && (board[URD].ptr)->isBlack() -isBlack != 0 && board[UURD].isEmpty()){
	newarr[index] = URD;
	Move *newmove = new Move(UURD, newarr);
	stack.push(newmove);
      }if(!board[LRD].isEmpty() && (board[LRD].ptr)->isBlack()-isBlack != 0 && board[LLRD].isEmpty()){
	newarr[index] = LRD;
	Move *newmove = new Move(LLRD, newarr);
	stack.push(newmove);
      }
    }
    return stack;
  }else{ //if the piece is not kinged
    if(isBlack){ //if the regular piece is black
      if(current_row >= 7){ //if the regular black piece is too close to the bottom of the board
	return stack;
      }else if (current_col <= 1){ //if the regular black piece is too close to the left side of the board
	if(!board[LRD].isEmpty() && !(board[LRD].ptr)->isBlack() && board[LLRD].isEmpty()){
	  newarr[index] = LRD;
	  Move *newmove = new Move(LLRD, newarr);
	  stack.push(newmove);
	}
      }else if (current_col >= 6){ //if the regular black piece is too close to the right side of the board
	if(!board[LLD].isEmpty() && !(board[LLD].ptr)->isBlack() && board[LLLD].isEmpty()){
	  newarr[index] = LLD;
	  Move *newmove = new Move(LLLD, newarr);
	  stack.push(newmove);
	}
      }else{ //if the regular black piece is in the middle of the board
	if(!board[LRD].isEmpty() && !(board[LRD].ptr)->isBlack() && board[LLRD].isEmpty()){
	   newarr[index] = LRD;
	  Move *newmove = new Move(LLRD, newarr);
	  stack.push(newmove);
	}
	if(!board[LLD].isEmpty() && !(board[LLD].ptr)->isBlack() && board[LLLD].isEmpty()){
	  newarr[index] = LLD;
	  Move *newmove = new Move(LLLD, newarr);
	  stack.push(newmove);
	}
      }
    }else{ //if the regular piece is red
      if(current_row <= 1){ //if the regular redi piece is too close to the top of the board
	return stack;
      }else if (current_col <= 1){ //if the regular red piece is too close to the left side of the board
	if(!board[URD].isEmpty() && (board[URD].ptr)->isBlack() && board[UURD].isEmpty()){
	   newarr[index] = URD;
	  Move *newmove = new Move(UURD, newarr);
	  stack.push(newmove);
	}
      }else if (current_col >= 6){ //if the regular red piece is too close to the right side of the board
	if(!board[ULD].isEmpty() && (board[ULD].ptr)->isBlack() && board[UULD].isEmpty()){
	  newarr[index] = ULD;
	  Move *newmove = new Move(UULD, newarr);
	  stack.push(newmove);
	}
      }else{ //if the regular red piece is in the middle of the board
	if(!board[URD].isEmpty() && (board[URD].ptr)->isBlack() && board[UURD].isEmpty()){
	  newarr[index] = URD;
	  Move *newmove = new Move(UURD, newarr);
	  stack.push(newmove);
	}
	if(!board[ULD].isEmpty() && (board[ULD].ptr)->isBlack() && board[UULD].isEmpty()){
	  newarr[index] = ULD;
	  Move *newmove = new Move(UULD, newarr);
	  stack.push(newmove);
	}
      }
    }
  }
  return stack;
}

Move ** CheckerBoard::getLegalMoves(int current_row, int current_col){ 
  int current = 8*current_row + current_col; //current index in the board
  Piece cur_piece = *(board[current].ptr);  //current Piece  
  int index = 0;
  int number = 0;
  int caps[12] = {};
  stack<Move *> final_stack = getSlides(current_row, current_col);
  stack<Move *> jump_stack = getJumps(current_row, current_col, caps, index, cur_piece.isBlack(), cur_piece.isKing());
  Move ** final_array = new Move *[100];
  while(!final_stack.empty()){
    final_array[number++] = final_stack.top();
    final_stack.pop();
  }
  while(!jump_stack.empty()){
    stack<Move *> temp = getJumps(jump_stack.top()->current/8,jump_stack.top()->current%8, jump_stack.top()->captured, ++index, cur_piece.isBlack(), cur_piece.isKing());
    final_array[number++] = jump_stack.top();
    jump_stack.pop();
    while(!temp.empty()){
      jump_stack.push(temp.top());
      temp.pop();
    }
  }
  return final_array;
}


void CheckerBoard::move(int current_row, int current_col, Move * move){ //move function
  int current = 8*current_row + current_col; //current index in the Board
  int proposed = move->current;
  int isBlack = board[current].ptr->isBlack();
  if(board[current].isEmpty() || (!(board[proposed].isEmpty())) || (move->current/8 + move->current%8)%2 == 0){ //if the proposal is bad print an error message (not complete)
    exit(1);
  }
  else{ //otherwise move the Piece to the proposed spot and remove it from the old Square
    int *ptr = move->captured;
    int i =0;
    while(ptr[i]!= 0){
      board[ptr[i]].removePiece();
      if(isBlack){
	numRed -= 1;	
      }else{
	numBlack -= 1;
      }
      i++;
    }
    if(proposed/8 ==7 && board[current].ptr->isBlack()){
      board[current].ptr->promote();
    }else if(proposed/8 ==0 && !(board[current].ptr->isBlack())){
      board[current].ptr->promote();
    }
    board[proposed].setPiece(board[current].ptr);
    board[current].removePiece();
  }
}
