#include<iostream>
#include<stdlib.h>
#include<string>
#include <stack>
#include <algorithm>
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
void CheckerBoard::refreshBoard(){
  for(int i=0; i<64; i++){
    	board[i].sqrefresh();
  }
}
int CheckerBoard::isCurrentEmpty(int current_row, int current_col){
  return board[8*current_row + current_col].isEmpty();
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
  Piece cur_piece = *(board[current].ptr);  //current Piece 
  if(cur_piece.isKing()){
    
  }else{
    if(cur_piece.isBlack()){ //if it's a black piece
      if(current%8 == 0){ //if it's on the left wall
	if(board[lowerRightDiagonal].isEmpty()){ //if the spot is empty
	  int *ptr =  new int[12];
	  Move *thisMove = new Move(lowerRightDiagonal, ptr); //add the new move to the stack
	  stck.push(thisMove);
	}
      }else if(current%8==7){ //if the black piece is on the right wall
	if(board[lowerLeftDiagonal].isEmpty()){
	  int *ptr = new int[12];
	  Move *thisMove = new Move(lowerLeftDiagonal, ptr);
	  stck.push(thisMove);
	}
      }else{ //if the black piece is in the middle
	if(board[lowerRightDiagonal].isEmpty()){
	  int *ptr =  new int[12];
	  Move *thisMove = new Move(lowerRightDiagonal, ptr); //Lower right
	  stck.push(thisMove);
	}
	if(board[lowerLeftDiagonal].isEmpty()){ 
	  int *ptr = new int[12];
	  Move *thisMove = new Move(lowerLeftDiagonal, ptr);
	  stck.push(thisMove);
	}
      }
    }else{ //if the piece is red
      if(current%8 == 0){ 
	if(board[upperRightDiagonal].isEmpty()){
	  int *ptr = new int[12];
	  Move *thisMove = new Move(upperRightDiagonal, ptr); //Lower right
	  stck.push(thisMove);
	}
      }else if(current%8==7){
	if(board[upperLeftDiagonal].isEmpty()){
	  int *ptr = new int[12];
	  Move *thisMove = new Move(upperLeftDiagonal, ptr);
	  stck.push(thisMove);
	}
      }else{
	if(board[upperRightDiagonal].isEmpty()){
	  int *ptr =  new int[12];
	  Move *thisMove = new Move(upperRightDiagonal, ptr); //Lower right
	  stck.push(thisMove);
	}
	if(board[upperLeftDiagonal].isEmpty()){
	  int *ptr = new int[12];
	  Move *thisMove = new Move(upperLeftDiagonal, ptr);
	  stck.push(thisMove);
	}
      }
    }
  }
  return stck;
}
stack<Move *> CheckerBoard::getJumps(int current_row, int current_col, int caps[12], int isBlack, int isKing){ //TODO: check that we're not backtracking
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

  //int ULD_captured = std::find(caps, caps + 12,  ULD) != caps+12;
  //int URD_captured = std::find(caps, caps + 12,  URD) != caps+12;
  //int LLD_captured = std::find(caps, caps + 12,  LLD) != caps+12;
  //int LRD_captured = std::find(caps, caps + 12,  LRD) != caps+12;
  int *first_zero = std::find(caps, caps + 12, 0);
  long index = (first_zero - caps)/sizeof(int);
  //cout <<index;
   if(isKing){
    
  }else{ //if the piece is not kinged
    if(isBlack){ //if the regular piece is black
      if(current_row >= 7){ //if the regular black piece is too close to the bottom of the board
	return stack;
      }else if (current_col <= 1){ //if the regular black piece is too close to the left side of the board
	if(!board[LRD].isEmpty() && !(board[LRD].ptr)->isBlack() && board[LLRD].isEmpty()){
	  caps[index] = LRD;
	  Move *newmove = new Move(LLRD, caps);
	  stack.push(newmove);
	}
      }else if (current_col >= 6){ //if the regular black piece is too close to the right side of the board
	if(!board[LLD].isEmpty() && !(board[LLD].ptr)->isBlack() && board[LLLD].isEmpty()){
	  caps[index] = LLD;
	  Move *newmove = new Move(LLLD, caps);
	  stack.push(newmove);
	}
      }else{ //if the regular black piece is in the middle of the board
	if(!board[LRD].isEmpty() && !(board[LRD].ptr)->isBlack() && board[LLRD].isEmpty()){
	   caps[index] = LRD;
	  Move *newmove = new Move(LLRD, caps);
	  stack.push(newmove);
	}
	if(!board[LLD].isEmpty() && !(board[LLD].ptr)->isBlack() && board[LLLD].isEmpty()){
	  caps[index] = LLD;
	  Move *newmove = new Move(LLLD, caps);
	  stack.push(newmove);
	}
      }
    }else{ //if the regular piece is red
      if(current_row <= 1){ //if the regular redi piece is too close to the top of the board
	return stack;
      }else if (current_col <= 1){ //if the regular red piece is too close to the left side of the board
	if(!board[URD].isEmpty() && (board[URD].ptr)->isBlack() && board[UURD].isEmpty()){
	   caps[index] = URD;
	  Move *newmove = new Move(UURD, caps);
	  stack.push(newmove);
	}
      }else if (current_col >= 6){ //if the regular red piece is too close to the right side of the board
	if(!board[ULD].isEmpty() && (board[ULD].ptr)->isBlack() && board[UULD].isEmpty()){
	  caps[index] = ULD;
	  Move *newmove = new Move(UULD, caps);
	  stack.push(newmove);
	}
      }else{ //if the regular red piece is in the middle of the board
	if(!board[URD].isEmpty() && (board[URD].ptr)->isBlack() && board[UURD].isEmpty()){
	   caps[index] = URD;
	  Move *newmove = new Move(UURD, caps);
	  stack.push(newmove);
	}
	if(!board[ULD].isEmpty() && (board[ULD].ptr)->isBlack() && board[UULD].isEmpty()){
	  caps[index] = ULD;
	  Move *newmove = new Move(UULD, caps);
	  stack.push(newmove);
	}
      }
    }
  }
  return stack;
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
    stack<Move *> slide_stack = getSlides(current_row, current_col);
    int caps[12] = {};
    stack<Move *> jump_stack = getJumps(current_row, current_col, caps, cur_piece.isBlack(), cur_piece.isKing());
    stack<Move *> alg_stack;
    stack<Move *> final_stack;
    while(!slide_stack.empty()){
      //cout << slide_stack.top()->current/8 << " " << slide_stack.top()->current%8 << endl;
      final_stack.push(slide_stack.top());
      slide_stack.pop();
    }
    while(!jump_stack.empty()){
      alg_stack.push(jump_stack.top());
      jump_stack.pop();
    }
    while(!alg_stack.empty()){
      stack<Move *> temp = getJumps(alg_stack.top()->current/8,alg_stack.top()->current%8, alg_stack.top()->captured, cur_piece.isBlack(), cur_piece.isKing());
      final_stack.push(alg_stack.top());
      alg_stack.pop();
      while(!temp.empty()){
	final_stack.push(temp.top());
	alg_stack.push(temp.top());
	temp.pop();
      }
    }
    while(!final_stack.empty()){
      cout << final_stack.top()->current/8 << " " << final_stack.top()->current%8 << " " << final_stack.top()->captured[0]<< " " << final_stack.top()->captured[1] <<endl;
      final_stack.pop();
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
    if(current - proposed > 9 || current -proposed < -9){
      board[proposed].setPiece(board[current].ptr);
      board[current].removePiece();
      int captured = (current+proposed)/2;
      board[captured].removePiece(); //TODO: increment a counter?
    }else{
    board[proposed].setPiece(board[current].ptr);
    board[current].removePiece();
    }
  }
}
