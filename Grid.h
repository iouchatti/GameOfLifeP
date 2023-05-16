#pragma once
#include <vector>
#include <iostream>
class Grid
{
public:
    using Matrix = std::vector<std::vector<bool>>;

    Grid(const Matrix& matrix) : m_matrix(matrix) {}
    void setCell(int row, int col, bool value) {
        m_matrix[row][col] = value;
    }
    bool getCell(int row, int col) const {
        return m_matrix[row][col];
    }
    size_t getRows() { 
        if (!m_matrix.empty())
            return m_matrix.size();
        else
            return 0;
    }
    size_t getCols(){
        if (!m_matrix.empty()) {
            if (!m_matrix[0].empty())
                return m_matrix[0].size();
        }
        return 0;
    }

    void extendMatrix(int left=1, int right=1, int top=1, int bottom=1); 
    Matrix reduceToSmallestMatrix();
    int calculateAliveNeighbors(int row, int col);
    void printMatrix(const std::string& input_filename, const unsigned int iteration);
 
    Matrix m_matrix;
};

