 #include <string>         
#include <chrono>
#include "ArgsParser.h"
#include "inputParser.h"
#include "rules.h"
#include "Game.h"

int main(int argc, char* argv[]) {

	// Initialize parser
	ArgsParser argsParser;
	cliOptions parameters = argsParser.parse_args(argc, argv);
	std::cout << "parameters :\ninput = " << parameters.input_file 
		<< "\niterations = " << parameters.iterations 
		<< "\nall = " << parameters.all << std::endl;


	// Create the input parser 
	std::string inputSourceType = "file";
	if (parameters.genRandomFile) {
		inputSourceType = "random";
	}
	InputParserFactory parserFactory;
	std::unique_ptr<InputParser> inputParser = parserFactory.createInputParser(inputSourceType);

	//Initialize grid 
	std::shared_ptr<Grid> grid = inputParser->parseInput(parameters.input_file);

	//Initialize rule of the game
	std::unique_ptr<GameRule> rule = std::make_unique<ConwaysRule>();

	// Initialize game with choosen rule 
	Game game(grid, std::move(rule));

	auto start = std::chrono::high_resolution_clock::now();

	//Run the game 
	game.runGame(parameters.input_file,parameters.iterations, parameters.all);


	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration = end - start;
	std::cout << "Execution time: " << duration.count() << " seconds" << std::endl;
	return 0;
}

