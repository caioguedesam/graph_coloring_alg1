#include "sudoku.h"

Cell::Cell() {
	value = -1;
}

Cell::Cell(int value) {
	this->value = value;
}

void Cell::ChangeValue(int value) {
	this->value = value;
}

void Cell::AddAdjacent(Cell *adj_cell) {
	adj_cells.push_back(adj_cell);
}

void Cell::PrintAllAdjacent() {
	for(int i = 0; i < adj_cells.size(); i++) {
		std::cout << adj_cells[i]->value << " -> ";
	}
	std::cout << std::endl;
}

Sudoku::Sudoku(int size, int width, int height) {
	board_size = size;
	quad_width = width;
	quad_height = height;
	cells = new Cell*[size];
	for(int i = 0; i < size; i++) {
		cells[i] = new Cell[size];
	}
}

Sudoku::~Sudoku() {
	for(int i = 0; i < board_size; i++) {
		delete[] cells[i];
	}

	delete[] cells;
}

void Sudoku::CreateSudoku() {
	for(int i = 0; i < board_size; i++) {
		for(int j = 0; j < board_size; j++) {
			int value;
			std::cin >> value;
			cells[i][j].ChangeValue(value);
		}
	}
}

void Sudoku::AddConections() {
	for(int i = 0; i < board_size; i++) {
		for(int j = 0; j < board_size; j++) {
			// Adicionando vizinhos da linha/coluna
			for(int k = 0; k < board_size; k++) {
				// Linha
				if(k != j)
					cells[i][j].AddAdjacent(&cells[i][k]);
				// Coluna
				if(k != i)
					cells[i][j].AddAdjacent(&cells[k][j]);
			}

			// Adicionando quadrantes
			for(int w = 0; w < board_size; w++) {
				for(int h = 0; h < board_size; h++) {
					if(i != w && j != h && 
						i/quad_width == w/quad_width &&
						j/quad_height == h/quad_height) {
						cells[i][j].AddAdjacent(&cells[w][h]);
					}
				}
			}
		}
	}
}

void Sudoku::PrintSudoku() {

	for(int i = 0; i < board_size; i++) {
		for(int j = 0; j < board_size; j++) {
			std::cout << cells[i][j].value << " ";
		}
		std::cout << std::endl;
	}

	std::cout << "Adjacents:" << std::endl;

	for(int i = 0; i < board_size; i++) {
		for(int j = 0; j < board_size; j++) {
			std::cout << "(" << i << "," << j << ")" << std::endl;
			cells[i][j].PrintAllAdjacent();
		}
	}

}
