#include <iostream>
#include <algorithm>
#include "move.h"
using namespace std;
   
Move::Move(){
  current = 0;
  int jumped[12] = {};
  captured = jumped;
}
Move::Move(int position, int jumped[12]){
  captured = new int[12];
  current = position;
  copy(jumped, jumped+12, captured);
}
