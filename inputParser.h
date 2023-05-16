#pragma once
#include <memory>
#include <vector>
#include <string>
#include <iostream>    
#include <fstream>
#include <stdexcept>
#include "Grid.h"
#include <random>


class InputParser {
public:
	virtual ~InputParser() = default;
	virtual std::shared_ptr<Grid> parseInput(const std::string& input) = 0;
};

class FileInputParser : public InputParser {
public:
	std::shared_ptr<Grid> parseInput(const std::string& input) override;
};

class randomGeneratedInputParser : public InputParser {
public:
	std::shared_ptr<Grid> parseInput(const std::string& input) override;
	void generateRandomDimensions() ;
	void setDimensions(int rows, int cols) {
		m_rows = rows;
		m_cols = cols;
	}
private:
	int m_cols = 0 ;
	int m_rows = 0;
};

class InputParserFactory {
public:
	std::unique_ptr<InputParser> createInputParser(const std::string& inputSourceType) {
		if (inputSourceType == "file") {
			return std::make_unique<FileInputParser>();
		}
		else if (inputSourceType == "random") {
			return std::make_unique<randomGeneratedInputParser>();
		}
		else {
			throw std::runtime_error("Unsupported input source type");
		}
	}
};
 
