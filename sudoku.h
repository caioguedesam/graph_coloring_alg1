#ifndef ALG1_TP3_SUDOKU
#define ALG1_TP3_SUDOKU
#include <iostream>
#include <cmath>
#include <vector>

class Cell {
public:
	// Valor da célula
	int value;
	// Lista de vizinhos
	std::vector<Cell*> adj_cells;		

	Cell();
	Cell(int value);

	// Muda o valor contido na célula
	void ChangeValue(int value);
	// Adiciona uma célula como vizinha dessa célula
	void AddAdjacent(Cell *adj_cell);
	// Mostra todos os vizinhos
	// 1º os de linha/coluna alternados, depois os de quadrantes.
	void PrintAllAdjacent();
};

class Sudoku {
public:
	// Tamanho do quadro
	int board_size;
	// Tamanho do quadrante
	int quad_width, quad_height;
	// Quadro
	Cell **cells;

	Sudoku(int size, int width, int height); 
	~Sudoku();

	// Cria e popula o quadro com células vazias
	void CreateSudoku();
	// Adiciona conexões entre vizinhos seguindo regras do sudoku
	void AddConections();
	// Mostra a disposição das células e depois a lista de vizinhos por célula
	void PrintSudoku();
};

#endif
