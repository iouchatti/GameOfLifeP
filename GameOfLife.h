#pragma once
#include<string>
#include<vector>
#include <bitset>
using Matrix = std::vector<std::vector<bool>>;

class GameOfLife {
private:
	Matrix m_matrix;
public:
	void runGame(const std::string& filename,const unsigned int iteration, const bool all);
	std::bitset<8> getNeighbours(int line, int column, int nbOfColumns, int nbOfLines);
	void extendMatrix(int left=1, int right=1, int top=1, int bottom=1);
	Matrix reduceToSmallestMatrix(Matrix matrix);
	void writeMatrixToFile(const std::string& input_filename, const unsigned int iteration);
	GameOfLife(const std::string filename);
	~GameOfLife() {};

};

