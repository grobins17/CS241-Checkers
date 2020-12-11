#include <iostream>
#include "move.h"

Move::Move(){
  current = 0;
  int jumped[12] = {};
  captured = jumped;
}
Move::Move(int position, int jumped[12]){
  captured = new int[12];
  current = position;
  std::copy(jumped, jumped + 12, captured);
}
void Move::zeroout(){
  captured[0] = 0;
}
