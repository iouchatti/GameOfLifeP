#include "inputParser.h"

void randomGeneratedInputParser::generateRandomDimensions() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 20);

    m_rows = dis(gen);
    m_cols = dis(gen);
}
std::shared_ptr<Grid> randomGeneratedInputParser::parseInput(const std::string& input) {
    if (m_rows == 0 || m_cols == 0) {
        generateRandomDimensions();
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    std::ofstream file(input);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open input file: " + input);
    }

    Grid::Matrix matrix;
    for (int i = 0; i < m_rows; ++i) {
        std::vector<bool> row;
        for (int j = 0; j < m_cols; ++j) {
            bool value = (dis(gen) == 0) ? true : false;
            row.push_back(value);
            char symbol = (value) ? '*' : '_';
            file << symbol;
        }
        file << std::endl;
        matrix.push_back(row);
    }

    file.close();
    std::cout << "Random matrix file generated: " << input << std::endl;

    return std::make_shared<Grid>(std::move(matrix));
}

std::shared_ptr<Grid> FileInputParser::parseInput(const std::string& filename) {
    Grid::Matrix matrix;

    try {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + filename);
        }

        std::string row;
        size_t nbCols = 0;

        while (std::getline(file, row)) {
            if (nbCols == 0) {
                nbCols = row.length();
            }
            else if (row.length() != nbCols) {
                throw std::runtime_error("Error: All lines in the file must have the same length");
            }

            std::vector<bool> rowData;
            for (char c : row) {
                if (c == '*') {
                    rowData.push_back(true);
                }
                else if (c == '_') {
                    rowData.push_back(false);
                }
                else {
                    throw std::runtime_error("Error: Invalid character in the input file");
                }
            }
            matrix.push_back(rowData);
        }

        file.close();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::exit(1);
    }

    return std::make_shared<Grid>(std::move(matrix));
}