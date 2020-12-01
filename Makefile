CFLAGS= -g -Wall -Werror -Wshadow -Wundef -Wconversion

main: piece.cpp
	g++ $(CFLAGS) -o piece piece.cpp
