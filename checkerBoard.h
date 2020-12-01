#include<iostream>
#include<string>

using namespace std;

class CheckerBoard{
public:
	void initBoard(){
		for(int y = 0; y < 8; y++){
			for(int x = 0; x < 8; x++){
				if((x % 2) == 0){
					board[y][x] = '[ ]';
				}
				else{
					board[y][x] = "[x]";
				}
			}
		}
	}
	void printBoard(){
		for(int y = 0; y < 8; y++){
			for(int x = 0; x < 8; x++){
				cout << board[y][x];
			}
		}
	}
private:
	char board[8][8];
}
