#include<iostream>
#include "piece.h"
#include "square.h"
#include "checkerBoard.h"

using namespace std;

int main(){
  int count = 0;
  int current_row = 0;
  int current_col = 0;
  int proposed_row = 0;
  int proposed_col = 0;
  CheckerBoard board;
  board.initBoard();
  board.printBoard();
  while(count < 5){
    cout << "Current row: " << endl;
    cin >> current_row;
    cout << "Current col: " << endl;
    cin >> current_col;
    board.getLegalMoves(current_row, current_col);
    cout << "Proposed row: " << endl;
    cin >> proposed_row;
    cout << "Proposed col: " << endl;
    cin >> proposed_col;
    board.move(current_row, current_col, proposed_row, proposed_col);
    board.printBoard();
    count++;
  }
}
