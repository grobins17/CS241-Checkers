#include<iostream>
#include "piece.h"
#include "square.h"
#include "checkerBoard.h"
#include "gui.h"
#include <ncurses.h>

using namespace std;

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

  //INPUT BOX
  int in_h, in_w, in_y, in_x;

  in_h = 1;
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
  
  //Start square
  Square startSquare = board.getSquare(7, 6);
  startSquare.highlight();

//TURNS
  //int count = 0;
  int ch;
  int current_row = 0;
  int current_col = 0;
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
          if(board.isCurrentEmpty(current_row,current_col)==0){
            //selected square is empty
 		break;
          }
          else {
	    //selected square is not empty
	    selected=1;
	    selected_row = current_row;
	    selected_col = selected_col;
    	    legalmoves = board.getLegalMoves(selected_row, selected_col);
	  }
	  break;
      default:
	      mvwprintw(inBox, 0, 0, "Please enter a valid input");
	      break;
    }
  }

  int i = 0;
  while (i < 100){
      mvwprintw(inBox, 0, 0, "row: %d, col:%d      ", legalmoves[i]->current/8, legalmoves[i]->current%8);
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
	  board.move(selected_row, selected_col, legalmoves[0]);
	}
	else{
		mvwprintw(inBox, 0, 0, "You cannot move here, there is a piece there");
	}
	break;
      
      default:
	mvwprintw(inBox, 0, 0, "Please enter a valid input");
	break;
    }
  }
  board.refreshBoard();

  // TURNS
  /*
  while(count < 10){
    cout << "Current row: " << endl;
    cin >> current_row;
    cout << "Current col: " << endl;
    cin >> current_col;
    if (board.isCurrentEmpty(current_row, current_col)) {
	cout << "Please choose a square that contains a checker piece." << "\n" << "\n";
	continue;
    }
    cout << "\n";
    cout << "Proposed row: " << endl;
    cin >> proposed_row;
    cout << "Proposed col: " << endl;
    cin >> proposed_col;
    board.printBoard();
    count++;
  }
  
  */
  //GUI
  getch(); //REFRESHES PARENT SCREEN OVER CHILDREN
  endwin(); //ends ncurses mode
}
