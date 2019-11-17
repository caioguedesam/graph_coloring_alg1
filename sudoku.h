#ifndef ALG1_TP3_SUDOKU
#define ALG1_TP3_SUDOKU
#include <iostream>
#include <cmath>
#include <vector>
#include <utility>
#include <algorithm>

class Cell {
public:
	// Valor da célula
	int value;
	// Posição da célula
	int pos_x, pos_y;
	// Número de vizinhos que já estão marcados
	int adj_marked;
	// Lista de vizinhos
	std::vector<Cell*> adj_cells;		

	Cell();
	Cell(int value);

	void ChangeValue(int value);
	void AddAdjacent(Cell *adj_cell);
};

class Sudoku {
public:
	// A heurísitca achou uma solução?
	bool found_solution;
	// Tamanho do quadro
	int board_size;
	// Tamanho do quadrante
	int quad_width, quad_height;

	// Quantidade de células marcadas
	int marked_cells;	
	// Quadro
	Cell **cells;

	bool has_colored;

	Sudoku(int size, int width, int height); 
	~Sudoku();

	void CreateSudoku();
	void AddConections();

	void TryToColor(Cell *cell);
	void Solve();

	void PrintSudoku();
};

#endif
