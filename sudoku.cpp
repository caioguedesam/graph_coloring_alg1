#include "sudoku.h"

Cell::Cell() {
	value = 0;
	adj_marked = 0;
}

Cell::Cell(int value) {
	this->value = value;
	adj_marked = 0;
}

void Cell::ChangeValue(int value) {
	this->value = value;
}

void Cell::AddAdjacent(Cell *adj_cell) {
	adj_cells.push_back(adj_cell);
	if(adj_cell->value != 0)
		adj_marked++;
}

Sudoku::Sudoku(int size, int width, int height) {
	board_size = size;
	quad_width = width;
	quad_height = height;
	cells = new Cell*[size];
	for(int i = 0; i < size; i++) {
		cells[i] = new Cell[size];
	}

	marked_cells = 0;
}

Sudoku::~Sudoku() {
	for(int i = 0; i < board_size; i++) {
		delete[] cells[i];
	}

	delete[] cells;
}

// CreateSudoku: Cria o tabuleiro e popula-o
// com 0s.
void Sudoku::CreateSudoku() {
	for(int i = 0; i < board_size; i++) {
		for(int j = 0; j < board_size; j++) {
			int value;
			std::cin >> value;
			cells[i][j].ChangeValue(value);
			cells[i][j].pos_x = i;
			cells[i][j].pos_y = j;
			if(value != 0)
				marked_cells++;
		}
	}
}

// AddConnections: adiciona todas as conexões entre células
// do Sudoku da mesma linha/coluna/quadrante
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

// PrintSudoku: imprime o resultado do jogo do sudoku.
void Sudoku::PrintSudoku() {

	if(CheckForValidSolution())
		std::cout << "solução" << std::endl;
	else
		std::cout << "sem solução" << std::endl;
	for(int i = 0; i < board_size; i++) {
		for(int j = 0; j < board_size; j++) {
			std::cout << cells[i][j].value << " ";
		}
		std::cout << std::endl;
	}
}

// TryToColor: Tenta marcar uma dada célula. Marca apenas
// caso a célula tenha uma possibilidade de marcação.
void Sudoku::TryToColor(Cell *cell, bool force_color) {

	// Todas as cores possíveis para uma dada célula
	std::vector<int> possible_colors;

	// Caso a célula esteja desmarcada
	if(cell->value == 0) {
		// Itera sobre todos os números e marca as que são possíveis
		// segundo os vizinhos dela
		for(int color = 1; color <= board_size; color++) {

			bool is_color_possible = true;

			// Se um vizinho já está marcado com o número atual,
			// a marcação não é válida. Vá para a próxima cor.
			for(int i = 0; i < cell->adj_cells.size(); i++) {
				if(color == cell->adj_cells[i]->value) {
					is_color_possible = false;
					break;
				}
			}

			// Caso não ache o número em nenhum vizinho, coloca a marcação
			// como possível.
			if(is_color_possible)
				possible_colors.push_back(color);
		}

		// Caso só haja uma cor possível, colore.
		if(possible_colors.size() == 1) {
			cell->value = possible_colors[0];
			marked_cells++;
			has_colored = true;
		}
		// Caso tente chutar, colore só se tiver 2 possibilidades
		else if(possible_colors.size() == 2 && force_color) {
			cell->value = possible_colors[0];
			marked_cells++;
			has_colored = true;
		}
	}
}

// Solve: resolve o sudoku
void Sudoku::Solve(int guess_tolerance) {

	int guesses = 0;

	// Continua iterando até que todas as células estejam marcadas
	while(marked_cells < (board_size * board_size) && guesses <= guess_tolerance) {
		// No início da iteração sobre o jogo, nenhuma célula
		// foi marcada na iteração

		has_colored = false;
		for(int i = 0; i < board_size; i++) {
			for(int j = 0; j < board_size; j++) {
				// Tenta colorir a dada célula
				TryToColor(&cells[i][j], false);
			}
		}

		// Caso nenhuma célula seja colorida com certeza,
		// hora de fazer um chute.
		if(!has_colored) {
			for(int i = 0; i < board_size; i++) {
				for(int j = 0; j < board_size; j++) {
					if(cells[i][j].value == 0) {
						TryToColor(&cells[i][j], true);
						if(has_colored) {
							guesses++;
							break;
						}
					}
				}
				if(has_colored)
					break;
			}
		}

		// Caso não hajam opções ou a tolerância de chutes seja ultrapassada,
		// pare.
		if(!has_colored || guesses > guess_tolerance)
			break;
	}

	// Padrão: achou solução
	//found_solution = CheckForValidSolution();
	/*// Caso seja encontrado um 0 na "solução", não
	// é solução válida.
	for(int i = 0; i < board_size; i++) {
		for(int j = 0; j < board_size; j++) {
			if(cells[i][j].value == 0)
				found_solution = false;
		}
	}*/

	// Imprime resultados
	PrintSudoku();
}

bool Sudoku::CheckForValidSolution() {
	for(int i = 0; i < board_size; i++) {
		for(int j = 0; j < board_size; j++) {
			Cell *current_cell = &cells[i][j];
			if(current_cell->value == 0)
				return false;
			else {
				std::vector<Cell*> adj = current_cell->adj_cells;
				for(int k = 0; k < adj.size(); k++) {
					if(adj[k]->value == current_cell->value)
						return false;
				}
			}
		}
	}

	return true;
}

