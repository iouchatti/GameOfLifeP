#include <iostream>  
#include <string>        
#include <fstream>  
#include <cstdlib>  
#include <vector>
#include "GameOfLife.h"
#include <random>
#include <thread>
#include <chrono>

using Matrix = std::vector<std::vector<bool>>;


struct cliOptions {
	std::string input_file;
	int iterations = 1;
	bool all = false;
	bool genRandomFile = false;
};

cliOptions parse_args(int argc, char* argv[]) {

	cliOptions options;

	for (int i = 1; i < argc; i++) {
		std::string key = argv[i];

		if (key == "--input") {
			if (i + 1 < argc && argv[i + 1][0] != '-') {
				options.input_file = argv[++i]; // to not process this argument again
			}
			else {
				std::cerr << "Error: --input value is missing\n";
				std::exit(1);
			}
		}
		if (key == "--iterations") {
			if (i + 1 < argc && argv[i + 1][0] != '-') {
				try { // to handle stoi limitations
					options.iterations = std::stoi(argv[++i]);
					if (options.iterations <= 0) {
						std::cerr << "Error: --iterations value should be a positive integer\n";
						std::exit(1);
					}
				}
				catch (std::invalid_argument& e) {
					std::cerr << "Error: --iterations parameter should be an integer\n";
					std::exit(1);
				}
				catch (std::out_of_range& e) {
					std::cerr << "Error: --iterations parameter is out of range\n";
					std::exit(1);
				}
			}
			else {
				std::cerr << "Error: --iterations parameter is missing\n";
				std::exit(1);
			}
		}
		else if (key == "--all") {
			options.all = true;
		}
		if (key == "--gen") {
			options.genRandomFile = true;
		}
	}

	// Check if mandatory options are provided
	if (options.input_file.empty()) {
		std::cerr << "Error: --input parameter is missing\n";
		std::exit(1);
	}
	if (options.iterations < 0) {
		std::cerr << "Error: --iterations parameter is missing\n";
		std::exit(1);
	}

	return options;
}

 
void generateRandomMatrixFile(const std::string& filename, int rows, int cols) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 1);

	std::ofstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Failed to open file: " << filename << std::endl;
		return;
	}

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			char value = (dis(gen) == 0) ? '*' : '_';
			file << value;
		}
		file << std::endl;
	}

	file.close();
	std::cout << "Random matrix file generated: " << filename << std::endl;
}


int main(int argc, char* argv[]) {


	// Get execution params 
	cliOptions parameters;

	parameters = parse_args(argc, argv);
	std::cout << "parameters :\ninput = " << parameters.input_file << "\niterations = " << parameters.iterations << "\nall = " << parameters.all << std::endl;

	if (parameters.genRandomFile) {
		generateRandomMatrixFile(parameters.input_file, 10, 16);
	}
		

	GameOfLife game(parameters.input_file);


	auto start = std::chrono::high_resolution_clock::now();

	game.runGame(parameters.input_file, parameters.iterations, parameters.all);

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration = end - start;
	std::cout << "Execution time: " << duration.count() << " seconds" << std::endl;

	return 0;
}