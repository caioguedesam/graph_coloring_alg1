#include <iostream>
#include "sudoku.h"

using namespace std;

int main() {

	int n, w, h;
	std::cin >> n >> w >> h;

	Sudoku *board = new Sudoku(n, w, h);

	board->CreateSudoku();
	board->AddConections();

	board->Solve();
	delete board;

	return 0;
}
