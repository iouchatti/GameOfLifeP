#include "GameOfLife.h"
#include <fstream> 
#include <string>
#include <iostream>         
#include <cstdlib>  

#define ALIVE '*'
#define DEAD '_'

GameOfLife::GameOfLife(const std::string filename)
{
	m_matrix.clear();
	try {
		std::ifstream file(filename);
		if (!file.is_open()) {
			throw std::runtime_error("Failed to open file: " + filename);
		}

		std::string row;
		size_t nbCols = 0;


		while (std::getline(file, row)) {

			if (nbCols == 0) nbCols = row.length(); // Store nbCols of the first line

			else if (row.length() != nbCols) {
				std::cerr << "Error: All lines in the file must have the same length" << std::endl;
				std::exit(1);
			}

			std::vector<bool> rowData;

			for (char c : row) {
				if (c == ALIVE) { 
					rowData.push_back(true);
				}
				else if (c == DEAD) {
					rowData.push_back(false);
				}
				else {
					std::cerr << "Error: Invalid character '" << c << "' in the input file" << std::endl;
					std::exit(1);
				}
			}
			m_matrix.push_back(rowData);
		}
		file.close();
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		std::exit(1);
	}
}

std::bitset<8> GameOfLife::getNeighbours(int line, int column, int nbOfColumns, int nbOfLines) {

	std::bitset<8> neighbours; 
	bool alive = true;
	int ngbRow; // neigbours rows
	int ngbCol; // neigbours cols
	int ngbIdx = 0;
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			ngbRow = line + i;
			ngbCol = column + j;
			if (ngbRow >= 0 && ngbRow < nbOfLines && ngbCol >= 0 && ngbCol < nbOfColumns) {
				if (!(ngbRow == line && ngbCol == column)) {
					neighbours.set(ngbIdx, m_matrix[ngbRow][ngbCol]);
					ngbIdx++;
				}
			}
		}
	}
	return neighbours;
}


void GameOfLife::runGame(const std::string& filename, const unsigned int iteration, const bool all)
{
	std::cout << "\nStart game of life =============" << std::endl;

	Matrix l_bMatrix;

	bool alive = true;
	bool dead = false;
	int nbCols = 0;
	int nbRows = 0;

	if (!m_matrix.empty()) {


		for (int it = 0; it < iteration;it++) {
			extendMatrix(); // as said in the exercise grid is infinite in all directions, we assume it is full of dead cells. 
			l_bMatrix = m_matrix ;
			nbCols = l_bMatrix[0].size(); // size of line/row
			nbRows = l_bMatrix.size();   // size column

			if (all) {
				std::cout << "\n=> Iteration Nb:" << it << "/"<<iteration<<"\n\n";
				writeMatrixToFile(filename, it);
			}
			for (int row = 0; row < nbRows;row++) { // we iterate over lines
				for (int col = 0; col < nbCols;col++) // bellow code is executed for one cell at a time, at (i, j) position
				{
					std::bitset<8> neighbours = getNeighbours(row, col, nbCols, nbRows);
					int aliveNeighboursCount = neighbours.count(); /* Count the number of true bits; if we used
																	a vector we could also optimize by automatically killing
																	the current cell when count exceeds 3 without checking next cells*/
					if ( (m_matrix[row][col] == alive && aliveNeighboursCount == 2) || aliveNeighboursCount == 3)
						 l_bMatrix[row][col] = alive;
					else l_bMatrix[row][col] = dead;
				}
			}
			m_matrix = reduceToSmallestMatrix(l_bMatrix);
			if (m_matrix.empty()) {
				std::cout << "\n====================================================" << std::endl;
				std::cout << "Population extinct  it is over  _(--)_/ Try again    " << std::endl;
				std::cout << "====================================================" << std::endl;
				return;
			}
		}
		std::cout << "\n\n=> Iteration Nb : " << iteration << "  \"Last one\"\n\n";
		writeMatrixToFile(filename, iteration);
	}
	else {
		std::cout << "\n====================================================" << std::endl;
		std::cout << "input file is empty, have more fun with a filled one" << std::endl;
		std::cout << "====================================================" << std::endl;
	}

}
void GameOfLife::writeMatrixToFile(const std::string& input_filename, const unsigned int iteration)
{
	// Generate the output filename
	std::string output_filename;
	size_t last_dot = input_filename.find_last_of(".");

	if (last_dot == std::string::npos) {
		// No extension in the input filename
		output_filename = input_filename + "_" + std::to_string(iteration);
	}
	else {
		// Input filename has an extension
		output_filename = input_filename.substr(0, last_dot) + "_" + std::to_string(iteration) + input_filename.substr(last_dot);
	}

	// Open the output file
	std::ofstream file(output_filename);
	if (!file.is_open()) {
		throw std::runtime_error("Failed to open file: " + output_filename);
	}

	// Write the matrix to the file
	for (const auto& row : m_matrix) {
		for (bool cell : row) {
			file << (cell ? '*' : '_');
		}
		file << '\n';
	}

	// Close the file
	file.close();
}

Matrix GameOfLife::reduceToSmallestMatrix(Matrix matrix)
{
	int minRow;
	int minCol;
	int maxRow = -1;        // Initialize the maximum row index to minimum	
	int maxCol = -1;        // Initialize the maximum column index to minimum
	int nbRows;
	int nbCols;

	if (!matrix.empty()) {
		minRow = nbRows = matrix.size();    // Initialize the minimum row index to maximum
		minCol = nbCols = matrix[0].size();    // Initialize the minimum column index to maximum

		// Find the bounding box of true cells
		for (int row = 0; row < nbRows; row++) {
			for (int col = 0; col < nbCols; col++) {
				if (matrix[row][col]) {
					minRow = std::min(minRow, row);
					maxRow = std::max(maxRow, row);
					minCol = std::min(minCol, col);
					maxCol = std::max(maxCol, col);
				}
			}
		}

		int nbBottomRowsToRemove = nbRows - (maxRow + 1);
		int nbRightColsToRemove = nbCols - (maxCol + 1);
		int nbTopRowsToRemove = minRow; 
		int nbLeftColsToRemove = minCol;

		if (nbBottomRowsToRemove > 0) matrix.erase(matrix.end() - nbBottomRowsToRemove, matrix.end());
		if (!matrix.empty()) {
			if (nbTopRowsToRemove > 0) matrix.erase(matrix.begin(), matrix.begin() + nbTopRowsToRemove);
			for (auto& row : matrix) {
				if (nbLeftColsToRemove > 0) row.erase(row.begin(), row.begin() + nbLeftColsToRemove);
				if (nbRightColsToRemove > 0) row.erase(row.end() - nbRightColsToRemove, row.end());

			}
		}

	}

	if (maxCol == -1 || minCol == -1) {
		matrix.clear();
	}
	return matrix;
}

void GameOfLife::extendMatrix(int left, int right, int top, int bottom) {

	int nbRows = m_matrix.size();
	int nbCols = nbRows > 0 ? m_matrix[0].size() : 0;

	int newNbRows = nbRows + top + bottom;
	
	// Extend rows at the top
	for (int i = 0; i < top; i++) {
		m_matrix.insert(m_matrix.begin(), std::vector<bool>(nbCols, false));
	}

	// Extend rows at the bottom
	for (int i = 0; i < bottom; i++) {
		m_matrix.push_back(std::vector<bool>(nbCols, false));
	}

	// Extend columns on the left and right
	for (int i = 0; i < newNbRows; i++) {
		// Extend columns on the left
		for (int j = 0; j < left; j++) {
			m_matrix[i].insert(m_matrix[i].begin(), false);
		}

		// Extend columns on the right
		for (int j = 0; j < right; j++) {
			m_matrix[i].push_back(false);
		}
	}

}