#include "ArgsParser.h"
#include "ArgsParser.h"
#include <iostream>

cliOptions ArgsParser::parse_args(int argc, char* argv[]) {
    cliOptions options;

    for (int i = 1; i < argc; i++) {
        std::string key = argv[i];

        if (key == "--input") {
            if (i + 1 < argc && argv[i + 1][0] != '-') {
                options.input_file = argv[++i]; 
            }
            else {
                std::cerr << "Error: --input value is missing\n";
                std::exit(1);
            }
        }
        else if (key == "--iterations") {
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
        else if (key == "--gen") {
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