
#ifndef MOVE_H
#define MOVE_H
#include <iostream>

using namespace std;
class Move{
 public:
  Move();
  Move(int, int current[]);
  int *captured;
  int current;
};
#endif
