#include <iostream>
#include <time.h>
#include <fstream>
#include <sstream>
#include "sudoku.h"

using namespace std;

int main(int argc, char *argv[]) {

	std::fstream file;
	file.open(argv[1]);
	std::string line;


	srand(time(NULL));

	int n, w, h;
	file >> n >> w >> h;

	Sudoku *board = new Sudoku(n, w, h);

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			int value;
			file >> value;
			board->cells[i][j].ChangeValue(value);
			board->cells[i][j].pos_x = i;
			board->cells[i][j].pos_y = j;
			if(value != 0)
				board->marked_cells++;
		}
	}

	board->AddConections();

	board->Solve(5);
	delete board;

	file.close();

	return 0;
}
