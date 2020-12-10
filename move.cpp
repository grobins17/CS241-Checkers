#include <iostream>
#include "move.h"

Move::Move(){
  current = 0;
  int jumped[12] = {};
  captured = jumped;
}
Move::Move(int position, int jumped[12]){
  current = position;
  captured = jumped;
}
