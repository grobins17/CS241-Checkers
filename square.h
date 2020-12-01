//Square Class

#include<iostream>
#include<piece.h>

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
	public:
		//calls constructor for the Square object 
		Square(int, int, int);	
		
		//gets row 
		int getRow(){
			return row;
		}
		
		//gets col
		int getCol(){
                        return col;
                }
		
		//gets type
		int getType(){
                        return type;
                }
		
		//need to make method to check if we have open spots. Can checkthe next squares type but will different parameters
}
// constructor for the Square object
Square::Square (int a, int b, int c){
	row = a;
	col = b;
	type = c;
}





