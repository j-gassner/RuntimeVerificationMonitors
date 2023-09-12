#pragma once

#include <string>
#include <vector>
#include "Algorithms.h"

class Settings{
public:
    bool past{false};
    size_t runs{1};
    std::vector<size_t> delays{0};
    std::vector<bool> lazyModes{false};
    std::vector<Algorithm> algorithms{dynamic};
    bool rebuildFSMsEveryRun{false};
    bool consoleOutput{true};
    std::string outputFile{"Evaluation.csv"};
};