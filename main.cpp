#include<iostream>
#include <stdlib.h>
#include <algorithm>
#include <ncurses.h>
#include <unistd.h>
#include "piece.h"
#include "square.h"
#include "checkerBoard.h"
#include "gui.h"

using namespace std;
int findLastElement(Move **legalmoves){
  int i = -1;
  for(; i < 100; i++){
    if (legalmoves[i+1] == NULL){
      break;
    }
  }
  return i;
}

void computerturn(CheckerBoard *theboard){
  CheckerBoard board = *(theboard);
  Move **goodmoves = new Move *[12];
  Move **legalmoves = new Move *[100];
  Square blackSquare;
  int index = 0;
  int what = 0;
  int *place = new int[12];
  for (int i = 0; i < 64; i++){
    blackSquare = board.getSquare(i/8, i %8);
    if(!blackSquare.isEmpty()){
      if(blackSquare.ptr->isBlack()){
	legalmoves = board.getLegalMoves(i/8, i%8);
	what = findLastElement(legalmoves);
	if(what >= 0){
	  place[index] = i;
	  goodmoves[index++] = legalmoves[what];
	}
      }
    }
  }
  board.move(place[0]/8, place[0]%8, goodmoves[0]);
}


void userturn(WINDOW *inBox, CheckerBoard *theboard){

  CheckerBoard board = *(theboard);
  Square startSquare = board.getSquare(7, 6);
  startSquare.highlight();

//TURNS

  int ch;
  int current_row = 7;
  int current_col = 6;
  int selected_row = 0;
  int selected_col = 0;
  int selected=0;

  Square current_square = startSquare;
  Move ** legalmoves = new Move *[100];
  while( selected != 1 ) {  
    ch = wgetch(inBox);
    mvwprintw(inBox, 0, 0, "Key pressed: %c", ch);
    switch(ch) {
      case KEY_DOWN:
	  //move down
          if(current_row==7)
            break;
          else{
            ++current_row;
	    current_square.sqrefresh();
	    current_square = board.getSquare(current_row, current_col);
	    current_square.highlight();
	  }
	  break;
      case KEY_RIGHT:
	// move right
          if(current_col==7)
          	break;
	  else{
            ++current_col;
	    current_square.sqrefresh(); //unhighlights
	    current_square = board.getSquare(current_row, current_col); 
	    current_square.highlight(); //highlights new current_square
	  }
	  break;
      case KEY_UP:
	// move up
          if(current_row==0)
            break;
          else{
            --current_row;	      
	    current_square.sqrefresh();
	    current_square = board.getSquare(current_row, current_col);
	    current_square.highlight();
	  }
        break;
      case KEY_LEFT:
	// move left
      	  if(current_col==0)
            break;
          else{
            --current_col;
	    current_square.sqrefresh();
	    current_square = board.getSquare(current_row, current_col);
	    current_square.highlight();
	  }
	  break;
      case 10: //ASCII for 10
	//select piece
          if(board.isCurrentEmpty(current_row,current_col)== 1){
            //selected square is empty
 		break;
          }
          else {
	    //selected square is not empty
	    selected_row = current_row;
	    selected_col = current_col;
	    legalmoves = board.getLegalMoves(selected_row, selected_col);
	    if(legalmoves[0] == NULL){ //list of moves is empty
	      mvwprintw(inBox, 0, 0, "That piece has no legal moves!");
	      selected = 0;
	    }else{
	      selected=1;
	    }	    
	  }
	  break;
      case 'Q':
	  endwin();
	  exit(0);
      default:
	mvwprintw(inBox, 0, 0, "Please enter a valid input");
	break;
    }
  }

  int i = 0;
  int islegal = 0;
  int legals[100] = {0};
  while (i < 100){
    if(legalmoves[i] != NULL){
      mvwprintw(inBox, i, 0, "row: %d, col:%d      ", legalmoves[i]->current/8, legalmoves[i]->current%8);
      board.getSquare(legalmoves[i]->current/8, legalmoves[i]->current%8).highlight();
      legals[i] = legalmoves[i]->current;
      i++;
    }else{
      break;
    }
  }
  //PIECE HAS BEEN SELECTED
  while (selected == 1){
    ch = wgetch(inBox);
    mvwprintw(inBox, 0, 0, "Key pressed: %c", ch);
    switch(ch) {
      case KEY_DOWN:
	  //move down
          if(current_row==7)
            break;
          else{
            ++current_row;
	    current_square.sqrefresh();
	    current_square = board.getSquare(current_row, current_col);
	    current_square.highlight();
	  }
	  break;
      case KEY_RIGHT:
	// move right
          if(current_col==7)
            break;
          else{
            ++current_col;
	    current_square.sqrefresh();
	    current_square = board.getSquare(current_row, current_col);
	    current_square.highlight();
	  }
	  break;
      case KEY_UP:
	// move up
          if(current_row==0)
            break;
          else{
            --current_row;	      
	    current_square.sqrefresh();
	    current_square = board.getSquare(current_row, current_col);
	    current_square.highlight();
	  }
        break;
      case KEY_LEFT:
	// move left
      	  if(current_col==0)
            break;
          else{
            --current_col;
	    current_square.sqrefresh();
	    current_square = board.getSquare(current_row, current_col);
	    current_square.highlight();
	  }
	  break;
      case 10: //ASCII for ENTER
	//select piece
	if (board.isCurrentEmpty(current_row, current_col)){
	  int *location = std::find(legals, legals + 100, current_row*8 + current_col);
	  islegal = (location != legals + 100);
	  if(islegal){
	    board.move(selected_row, selected_col, legalmoves[distance(legals, location)]);
	    mvwprintw(inBox, 1, 0, "Number Black: %d", board.numBlack);
	    mvwprintw(inBox, 2, 0, "Number Red: %d", board.numRed);
	    board.getSquare(selected_row, selected_col).sqrefresh();
	    board.getSquare(current_row, current_col).sqrefresh();
	    selected = 0;
	    current_square = board.getSquare(current_row, current_col);
	  }else{
	    mvwprintw(inBox, 0, 0, "That is not a valid move");
	    break;
	  }
	}
	else{
	  mvwprintw(inBox, 0, 0, "You cannot move here, there is a piece there");
	}
	break;  
      case 'Q':
	  endwin();
	  exit(0);
      default:
	mvwprintw(inBox, 0, 0, "Please enter a valid input");
	break;
    }
  }
  board.refreshBoard();
}




int main(){
  
  //GUI
  initscr(); //makes screen
  raw(); //disables line buffer, AKA you don't have to press enter for getch and wgetch
  noecho(); //disables input displaying on screen
  start_color(); //enables colors
  
  //COLOR PAIRS
  //White square
  init_pair(1, COLOR_WHITE, COLOR_WHITE);
  //Black square/piece
  init_pair(2, COLOR_BLACK, COLOR_BLACK);
  //Red piece
  init_pair(3, COLOR_RED, COLOR_RED);
  //Screen border
  init_color(COLOR_MAGENTA, 500, 500, 500);
  init_pair(4, COLOR_MAGENTA, COLOR_MAGENTA);
  //King Piece
  init_color(COLOR_YELLOW, 1000, 800, 100);
  init_pair(5, COLOR_YELLOW, COLOR_YELLOW);
  //Highlight
  init_pair(6, COLOR_CYAN, COLOR_CYAN);
  
  //TITLE BOX
  int title_h, title_w, title_y, title_x;

  title_h = 3;
  title_w = 10;
  title_y = 3;
  title_x = (COLS - title_w) / 2;

  WINDOW *title = newwin(title_h, title_w, title_y, title_x);
  box(title, 0, 0);
  mvwprintw(title, 1, 1, "CHECKERS");
  wrefresh(title); 
  
  //BOARD EDGE
  int edge_h, edge_w, edge_y, edge_x;

  edge_h = 26;
  edge_w = 50;
  edge_y = (LINES/6) - 1;
  edge_x = (COLS/2) - 25;

  WINDOW *edge = newwin(edge_h, edge_w, edge_y, edge_x);
  wattron(edge, COLOR_PAIR(4));
  box(edge, 0, 0);
  wattroff(edge, COLOR_PAIR(4));
  wrefresh(edge);
  //CONTROLS
  int control_h, control_w, control_y, control_x;

  control_h = 26;
  control_w = 20;
  control_y = LINES/6 - 1;
  control_x = 3;

  WINDOW* control = newwin(control_h, control_w, control_y, control_x);
  box(control, 0, 0);
  mvwprintw(control, 1, 6, "CONTROLS");
  mvwprintw(control, 3, 1, "ACTION -> KEY");
  mvwprintw(control, 5, 1, "Move -> Arrow Keys");
  mvwprintw(control, 6, 1, "Select -> Enter");
  mvwprintw(control, 7, 1, "Quit -> Q");
  wrefresh(control);

  //INPUT BOX
  int in_h, in_w, in_y, in_x;
  
  in_h = 3;
  in_w = COLS;
  in_y = (5 * LINES) / 6;
  in_x = 0;

  WINDOW *inBox = newwin(in_h, in_w, in_y, in_x);
  wrefresh(inBox);
  
  //BOARD INITIALIZATION
  CheckerBoard board;
  board.initBoard();
  board.refreshBoard();

  //wgetch(title);
  keypad(inBox, TRUE); //enables usage of arrow keys
  int turns = 0;
  while(turns < 100 && board.numRed > 0 && board.numBlack > 0){
    userturn(inBox, &board);
    computerturn(&board);
    board.refreshBoard();
  }
  usleep(3000000);
  //GUI
  //getch(); //REFRESHES PARENT SCREEN OVER CHILDREN
  endwin(); //ends ncurses mode
}
