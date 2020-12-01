#include<iostream>
#include<string>
#include "square.cpp"

using namespace std;

class CheckerBoard{
 public:
  void initBoard();
  void printBoard();
private:
  Square board[8][8];
}
