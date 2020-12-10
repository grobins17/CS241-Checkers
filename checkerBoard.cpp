#include<iostream>
#include<stdlib.h>
#include<string>
#include <stack>
#include "checkerBoard.h"


using namespace std;

CheckerBoard::CheckerBoard(){ //constructor
  Square* arr = new Square[64]; //make the board (now a one-dimensional array of Squares)
  for(int i = 0; i < 64; i++){
    arr[i] = Square(i/8,i%8, NULL); //initialize all the Squares in the board
  }
  board = arr; //change the checkerBoard attribute to point at initialized array
  
  // initialize all the spots in blackLegal array
  int* black = new int[10];
  for(int j = 0; j < 10; j++){
    black[j] = -1;
  }
  blackLegal = black;

  // initialize all the spots in redLegal array
  int* red = new int[10];
  for(int z = 0; z < 10; z++){
    red[z] = -1;
  }
  redLegal = red;

  // initialize all the spots in blackLegal array
  int* blackC = new int[10];
  for(int j = 0; j < 10; j++){
    blackC[j] = -1;
  }
  blackCapture = blackC;

  // initialize all the spots in redLegal array
  int* redC = new int[10];
  for(int z = 0; z < 10; z++){
    redC[z] = -1;
  }
  redCapture = redC;

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

int CheckerBoard::isCurrentEmpty(int current_row, int current_col){
  return board[8*current_row + current_col].isEmpty();
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

void CheckerBoard::printArray(int *arr, int current){
  for(int i = 0; i < 10; i++){ // goes through each value of the list
    if(arr[i] != -1){  
      if(arr[i] < current){ //checks if the new piece is less than the current. If so, it is on an upper row
        cout << "Row: " << current/8 - 1 << " ";
      }
      else if(arr[i] > current){ // checks if the new piece is greater than current. If so, it is on a lower row
	cout << "Row: " << current/8 + 1 << " ";
      }
      else{//debugging purposes
 	continue;
      }
      cout << "Col: " << arr[i]%8 << "\n"; // array holds the new location and we can use it to find the col
    }
    else{
      continue;
    }
  }
}
stack<Move *> CheckerBoard::getSlides(int current_row, int current_col){
  std::stack<Move *> stck;
  int current = 8*current_row + current_col; //current index in the board
  int upperLeftDiagonal = current - 9;
  int upperRightDiagonal = current -7;
  int lowerRightDiagonal = current + 9;
  int lowerLeftDiagonal = current +7;
  cout << "Possible moves: \n";
  Piece cur_piece = *(board[current].ptr);  //current Piece 
  if(cur_piece.isKing()){
    
  }else{
    if(cur_piece.isBlack()){ //if it's a black piece
      if(current%8 == 0){ //if it's on the left wall
	if(board[lowerRightDiagonal].isEmpty()){ //if the spot is empty
	  int *ptr =  new int[12];
	  cout << lowerRightDiagonal/8 << " " << lowerRightDiagonal%8 << endl;
	  Move *thisMove = new Move(lowerRightDiagonal, ptr); //add the new move to the stack
	  stck.push(thisMove);
	}
      }else if(current%8==7){ //if the black piece is on the right wall
	if(board[lowerLeftDiagonal].isEmpty()){
	  int *ptr = new int[12];
	  cout << lowerLeftDiagonal/8 << " " << lowerLeftDiagonal%8 << endl;
	  Move *thisMove = new Move(lowerLeftDiagonal, ptr);
	  stck.push(thisMove);
	}
      }else{ //if the black piece is in the middle
	if(board[lowerRightDiagonal].isEmpty()){
	  int *ptr =  new int[12];
	  cout << lowerRightDiagonal/8 << " " << lowerRightDiagonal%8 << endl;
	  Move *thisMove = new Move(lowerRightDiagonal, ptr); //Lower right
	  stck.push(thisMove);
	}
	if(board[lowerLeftDiagonal].isEmpty()){ 
	  int *ptr = new int[12];
	  cout << lowerLeftDiagonal/8 << " " << lowerLeftDiagonal%8 << endl;
	  Move *thisMove = new Move(lowerLeftDiagonal, ptr);
	  stck.push(thisMove);
	}
      }
    }else{ //if the piece is red
      if(current%8 == 0){ //if
	if(board[upperRightDiagonal].isEmpty()){
	  int *ptr = new int[12];
	  cout << upperRightDiagonal/8 << " " << upperRightDiagonal%8 << endl;
	  Move *thisMove = new Move(upperRightDiagonal, ptr); //Lower right
	  stck.push(thisMove);
	}
      }else if(current%8==7){
	if(board[upperLeftDiagonal].isEmpty()){
	  int *ptr = new int[12];
	  cout << upperLeftDiagonal/8 << " " << upperLeftDiagonal%8 << endl;
	  Move *thisMove = new Move(upperLeftDiagonal, ptr);
	  stck.push(thisMove);
	}
      }else{
	if(board[upperRightDiagonal].isEmpty()){
	  int *ptr =  new int[12];
	  cout << upperRightDiagonal/8 << " " << upperRightDiagonal%8 << endl;
	  Move *thisMove = new Move(upperRightDiagonal, ptr); //Lower right
	  stck.push(thisMove);
	}
	if(board[upperLeftDiagonal].isEmpty()){
	  int *ptr = new int[12];
	  cout << upperLeftDiagonal/8 << " " << upperLeftDiagonal%8 << endl;
	  Move *thisMove = new Move(upperLeftDiagonal, ptr);
	  stck.push(thisMove);
	}
      }
    }
  }
  return stck;
}
stack<Move *> CheckerBoard::getJumps(int current_row, int current_col, int *captured){
  stack<Move *> stack;
  int current = 8*current_row + current_col; //current index in the board
  int upperLeftDiagonal = current - 9;
  int upperRightDiagonal = current -7;
  int lowerRightDiagonal = current + 9;
  int lowerLeftDiagonal = current +7;
  Piece cur_piece = *(board[current].ptr);  //current Piece
  if(cur_piece.isKing()){

  }else{
    if(cur_piece.isBlack()){

    }else{


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
      if(current%8 == 0){ // checks if the piece is on the left wall of board
	if(board[lowerRightDiagonal].isEmpty()){//checks if left diagonal is empty
	  blackLegal[3] = lowerRightDiagonal; 
	}
	else if(board[upperRightDiagonal].isEmpty()){//checks if right diagonal is empty
	  blackLegal[1] = upperRightDiagonal;
	}
	else{
	  cout << "Sorry, there are no legal moves :(";
	}
      } 
      else if(current%8 == 7){ // checks if piece is on the right wall
	if(board[lowerLeftDiagonal].isEmpty()){//checks if left diagonal is empty
	  blackLegal[2] = lowerLeftDiagonal;
	}
	else if(board[upperLeftDiagonal].isEmpty()){//checks if right diagonal is empty
	  blackLegal[0] = upperLeftDiagonal;
	}
	else{
	  cout << "Sorry, there are no legal moves :(";
	} 
      }
      else{ //A regular piece that is in the middle of the board
	if(board[upperLeftDiagonal].isEmpty() && board[upperRightDiagonal].isEmpty()&& board[lowerLeftDiagonal].isEmpty() && board[lowerRightDiagonal].isEmpty()){
	  blackLegal[0] = upperLeftDiagonal;
	  blackLegal[1] = upperRightDiagonal;
	  blackLegal[2] = lowerLeftDiagonal;
	  blackLegal[3] = lowerRightDiagonal;
	}
	else if(!board[lowerRightDiagonal].isEmpty() && board[lowerLeftDiagonal].isEmpty()){
	  blackLegal[2] = lowerLeftDiagonal;
	}
	else if(!board[lowerLeftDiagonal].isEmpty() && board[lowerRightDiagonal].isEmpty()){
	  blackLegal[3] = lowerRightDiagonal;
	}
	else if(!board[upperRightDiagonal].isEmpty() && board[upperLeftDiagonal].isEmpty()){
	  blackLegal[0] = upperLeftDiagonal;
	}
	else if(!board[upperLeftDiagonal].isEmpty() && board[upperRightDiagonal].isEmpty()){
	  blackLegal[1] = upperRightDiagonal;
	}
	else{
	  cout << "Sorry, there are no legal moves :(";
	}
      }
      printArray(blackLegal,current);
    }
    else{ //piece is red 
	if(current%8 == 0){ // checks if the piece is on the left wall of board
	  if(board[lowerRightDiagonal].isEmpty()){//checks if left diagonal is empty
	    redLegal[3] = lowerRightDiagonal;   
	  }
	  else if(board[upperRightDiagonal].isEmpty()){//checks if right diagonal is empty
	    redLegal[1] = upperRightDiagonal;
	  }
	  else{
	    cout << "Sorry, there are no legal moves :(";
	  }
	}  
	else if(current%8 == 7){ // checks if piece is on the right wall
	  if(board[lowerLeftDiagonal].isEmpty()){//checks if left diagonal is empty
	    redLegal[2] = lowerLeftDiagonal;
	  }
	  else if(board[upperLeftDiagonal].isEmpty()){//checks if right diagonal is empty
	    redLegal[0] = upperLeftDiagonal;
	  }
	  else{
	    cout << "Sorry, there are no legal moves :(";
	  }
	}
	else{ // regular piece
	  if(board[upperLeftDiagonal].isEmpty() && board[upperRightDiagonal].isEmpty()&& board[lowerLeftDiagonal].isEmpty() && board[lowerRightDiagonal].isEmpty()){
	    redLegal[0] = upperLeftDiagonal;
	    redLegal[1] = upperRightDiagonal;
	    redLegal[2] = lowerLeftDiagonal;
	    redLegal[3] = lowerRightDiagonal;
	  }
	  else if(!board[lowerRightDiagonal].isEmpty() && board[lowerLeftDiagonal].isEmpty()){
	    redLegal[2] = lowerLeftDiagonal; 
	  }
	  else if(!board[lowerLeftDiagonal].isEmpty() && board[lowerRightDiagonal].isEmpty()){
	    redLegal[3] = lowerRightDiagonal;
	  }
	  else if(!board[upperRightDiagonal].isEmpty() && board[upperLeftDiagonal].isEmpty()){
	    redLegal[0] = upperLeftDiagonal;
	  }
	  else if(!board[upperLeftDiagonal].isEmpty() && board[upperRightDiagonal].isEmpty()){
	    redLegal[1] = upperRightDiagonal;
	  }
	  else{
	    cout << "Sorry, there are no legal moves :(";
	  }
	}
	printArray(redLegal,current);
    }
  }else{
    stack<Move *> stck = getSlides(current_row, current_col);
    cout << endl;
    while(!stck.empty()){
      cout << stck.top()->current/8 << " " << stck.top()->current%8 << endl;
      stck.pop();
    }
  }
}

void CheckerBoard::move(int current_row, int current_col, int proposed_row, int proposed_col){ //move function
  int current = 8*current_row + current_col; //current index in the Board
  int proposed = 8*proposed_row + proposed_col; //proposed index in the Board
  if(board[current].isEmpty() || (!(board[proposed].isEmpty())) || (proposed_row + proposed_col)%2 == 0){ //if the proposal is bad print an error message (not complete)
    cout << "that's no good!" << "\n" << "\n";
  }
  else{ //otherwise move the Piece to the proposed spot and remove it from the old Square
    board[proposed].setPiece(board[current].ptr);
    board[current].removePiece();
  }
}

// checks to see if it is possible to catch a piece
// returns 0 for False, 1 for True
// direction gives a number indication of where the piece is hoping to go.
// 0 is for upper left, 1 is for upper right, 2 is for lower left, 3 is for lower right 
// captures the new piece
int CheckerBoard::canCapture(int current, int direction){
  int difference;
  if(direction == 0){
    difference = -9;
  }
  else if(direction == 1){
    difference = -7;
  }
  else if(direction == 2){
    difference = 7;
  }
  else if(direction == 3){
    difference = 9;
  }
  else{ // will not give anything
    difference = 0;
  }

  int capture_ending = current + difference; // depending on the difference diven is the amount needed to be added to the current amount to get the index of the new spot.

  if(board[capture_ending].isEmpty()){
     return 1;
  }
  else{
     return 0;
  }
}

// used in move method 
/*
void CheckerBoard::capture(int current_row, int current_col, int proposed_row, int proposed_col){
  int current = 8*current_row + current_col; //current index in the Board
  int proposed = 8*proposed_row + proposed_col; //proposed index in the Board
    
}*/	
