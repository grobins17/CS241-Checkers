//Square Class
//Hi miles

#include<iostream>
#include "square.h"
#include <ncurses.h>

using namespace std;

//unparameterized constructor (for setup)
Square::Square(){ 
  row = 0;
  col = 0;
  ptr = NULL;
}
// constructor for the Square object
Square::Square (int a, int b, Piece *piece){
	row = a;
	col = b;
	ptr = piece;
        
	//GUI
	initWindow();
}
int Square::getCol(){ //returns column
  return col;
}
void Square::setCol(int c){ //sets column
  col = c;
}
int Square::getRow(){ //returns row
  return row;
}
void Square::setRow(int r){//sets row
  row = r;
}
int Square::isEmpty(){ //returns true if no pointer to a Piece is in the square
  return (ptr == NULL);
}
void Square::setPiece(Piece * newPiece){ //changes the pointer to a Piece in the square
  ptr = newPiece;
}
void Square::removePiece(){ //removes the pointer to the Piece
  ptr = NULL;
}

void Square::initWindow(){
	int win_h, win_w, win_y, win_x;
	win_h = 3;
	win_w = 6;
	win_y = (LINES/6) + (3*row);
	win_x = ((COLS/2) - 24) + (6*(col%8));

	window = newwin(win_h, win_w, win_y, win_x);
        box(window, 0, 0);
	
	sqrefresh();	
}

//GUI COMPONENTS
WINDOW * Square::getWindow(){
  return window;
}

void Square::sqrefresh(){
  //SQUARE COLORS
  if ((row-col) % 2 == 0){ //black square
    wattron(window, COLOR_PAIR(2));
    box(window, 0, 0);
    mvwprintw(window, 1, 1, "    ");
    wattroff(window, COLOR_PAIR(2));
  }
  else { //white square
    wattron(window, COLOR_PAIR(1));
    box(window, 0, 0);
    mvwprintw(window, 1, 1, "    ");
    wattroff(window, COLOR_PAIR(1));
  } 

  //PIECES
  //// Is there a piece?
  if (isEmpty() == 1){ //If the square does not have a piece, exit
    //wprintw(window, "r: %d c: %d", row, col);
    wrefresh(window);
    return;
  }
  // What color is the piece?
  if (ptr->isBlack() == 1){ //returns 1 if black piece, 0 if red
    //Piece is black
    wattron(window, COLOR_PAIR(2));
    mvwprintw(window, 1, 1, "    ");
    wattroff(window, COLOR_PAIR(2));
  }
  else {
    //Piece is red
    wattron(window, COLOR_PAIR(3));
    mvwprintw(window, 1, 1, "    ");
    wattroff(window, COLOR_PAIR(3));
  }

  // Is the piece a king?
  if (ptr->isKing() == 1) {
    //Piece is a king
    wattron(window, COLOR_PAIR(5));
    mvwprintw(window, 1, 2, "  ");
    wattroff(window, COLOR_PAIR(5));
  }

  wrefresh(window);
}

void Square::highlight(){
  sqrefresh();
  wattron(window, COLOR_PAIR(6) | A_BLINK);
  box(window, 0, 0);
  wattroff(window, COLOR_PAIR(6) | A_BLINK);
  wrefresh(window);
}
