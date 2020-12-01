//Square Class

#include<iostream>
#include "square.h"

using namespace std;

// constructor for the Square object
Square::Square (int a, int b, int c){
	row = a;
	col = b;
	type = c;
}
int Square::getCol(){
  return col;
}
int Square::getRow(){
  return row;
}
int Square::getType(){
  return type;
}
