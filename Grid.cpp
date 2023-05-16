#include "Grid.h"
#include<string>
#include<fstream>

int Grid::calculateAliveNeighbors(int row, int col) {
	int aliveNeighbors = 0;
	int nbRows = getRows();
	int nbCols = getCols();

	// Check the 8 surrounding cells
	for (int i = row - 1; i <= row + 1; i++) {
		for (int j = col - 1; j <= col + 1; j++) {
			// Skip the current cell
			if (i == row && j == col) {
				continue;
			}

			// Check if the cell is within the grid bounds
			if (i >= 0 && i < nbRows && j >= 0 && j < nbCols) {
				// Check if the cell is alive
				if (getCell(i, j)) {
					aliveNeighbors++;
				}
			}
		}
	}
	return aliveNeighbors;
}

Grid::Matrix Grid::reduceToSmallestMatrix() {
	int minRow = -1, minCol = -1, maxRow = -1, maxCol = -1;
	int nbRows, nbCols;

	if (!m_matrix.empty()) {
		minRow = nbRows = m_matrix.size();
		minCol = nbCols = m_matrix[0].size();

		// Find the bounding box of true cells
		for (int row = 0; row < nbRows; row++) {
			for (int col = 0; col < nbCols; col++) {
				if (m_matrix[row][col]) {
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

		if (nbBottomRowsToRemove > 0) m_matrix.erase(m_matrix.end() - nbBottomRowsToRemove, m_matrix.end());
		if (!m_matrix.empty()) {
			if (nbTopRowsToRemove > 0) m_matrix.erase(m_matrix.begin(), m_matrix.begin() + nbTopRowsToRemove);
			for (auto& row : m_matrix) {
				if (nbLeftColsToRemove > 0) row.erase(row.begin(), row.begin() + nbLeftColsToRemove);
				if (nbRightColsToRemove > 0) row.erase(row.end() - nbRightColsToRemove, row.end());
			}
		}

	}
	else if (maxCol == -1 || minCol == -1) {
		m_matrix.clear(); // TODO send logs
	}
	else {
		return Grid::Matrix(0);// TODO send logs
	}
	return m_matrix;
}

void  Grid::extendMatrix(int left, int right, int top, int bottom) {
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

void  Grid::printMatrix(const std::string& input_filename, const unsigned int iteration)
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
			std::cout << (cell ? '*' : '_'); 
		}
		std::cout << '\n';
		file << '\n';
	}
	file.close();

}
