//Square Class

#include<iostream>
//#include<piece.h>

using namespace std;

class Square{
  //Values unless specified automatically are turned to private
  
  //row the square is located in the 2D array
  int row;
  
  //col the square is located in the 2D array
  int col;
  
  //the type that is being held in square
  //0 is represents the square is empty
  //1 is for user piece
  //2 is for computer's piece
  int type;

  Piece * ptr;
 public:
  //calls constructor for the Square object 
  Square(int, int, int);	
  
  //gets row 
  int getRow();
		
  //gets col
  int getCol();
  
  //gets type
  int getType();

  void setPiece(Piece * new);

  void removePiece();
};





