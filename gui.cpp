#include <iostream>
#include <ncurses.h>
#include "gui.h"
   
using namespace std;

void display_title()
{	

	// initialize title
	WINDOW *title;
	int title_h, title_w, title_x, title_y;

	// assign values
	title_h = 3;
	title_w = 10;
	title_x = (COLS - title_w) / 2;
	title_y = 3;

	// create window
	title = newwin(title_h, title_w, title_y, title_x);

	//create outline
	box(title, 0, 0);
	
	//print name
	mvwprintw(title, 1, 1, "CHECKERS");

	//display window
	wrefresh(title);
	refresh();
}
