tp3: main.o sudoku.o
	g++ main.o sudoku.o -o tp3
	make clean

main.o: main.cpp
	g++ -c main.cpp

sudoku.o: sudoku.cpp sudoku.h
	g++ -c sudoku.cpp -O3

clean:
	rm *.o
