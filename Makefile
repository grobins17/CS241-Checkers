CFLAGS= -O -g -Wall -Werror -Wshadow -Wundef -Wconversion

main: main.o piece.o square.o checkerBoard.o
	g++ $(CFLAGS) -o main main.cpp piece.o square.o checkerBoard.o
piece.o: piece.cpp piece.h
	g++ $(CFLAGS) -c piece.cpp
square.o: square.cpp square.h
	g++ $(CFLAGS) -c square.cpp
checkerBoard.o: checkerBoard.cpp checkerBoard.h
	g++ $(CFLAGS) -c checkerBoard.cpp
clean:
	rm -f main *.o
