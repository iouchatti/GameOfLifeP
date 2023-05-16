#pragma once
#include <vector>
#include <string>

struct cliOptions {
    std::string input_file;
    int iterations = 1;
    bool all = false;
    bool genRandomFile = false;
};

class ArgsParser {
public:
    cliOptions parse_args(int argc, char* argv[]);
};

