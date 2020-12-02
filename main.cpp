#include<iostream>
#include "piece.h"
#include "square.h"
#include "checkerBoard.h"

using namespace std;

int main(){
  cout << "hi mom" << endl;
  Piece piece(1,1);
  CheckerBoard board;
  board.initBoard();
  board.printBoard();
}
