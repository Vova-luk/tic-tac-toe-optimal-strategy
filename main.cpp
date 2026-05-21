#include "./tic_tac_toe.hpp"
#include <cstddef>
#include <fstream>
#include <iostream>

bool ReadInputFile(
    const std::string& path,
    std::vector<std::string>& lines,
    Error& error
) {
    std::ifstream input(path);
    std::string line;

    if (!input.is_open()) {
        error.type = INPUT_FILE_ERROR;
        error.file_path = path;
        error.row = NO_POSITION;
        error.column = NO_POSITION;
        return false;
    }

    lines.clear();

    while (std::getline(input, line)) {
        if (!line.empty() && line[line.size() - 1] == '\r') {
            line.erase(line.size() - 1);
        }

        lines.push_back(line);

        if (lines.size() >= MAX_READABLE_LINES) {
            break;
        }
    }

    return true;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> lines;
    StrategyTask task;
    Error error;
    TicTacToeSolver solver;
    DotFileWriter writer;
    TreeNode* result_tree = 0;
    GameResult result;

    error.type = NO_ERROR;
    error.file_path = "";
    error.row = NO_POSITION;
    error.column = NO_POSITION;

    if (argc != 3) {
        std::cout << "Использование: " << argv[0] << " <input.txt> <output.dot>\n";
        return 1;
    }

    if (!ReadInputFile(argv[1], lines, error)) {
        std::cout << error.GetMessage() << '\n';
        return 1;
    }

    if (!ParseStrategyTask(lines, task, error)) {
        std::cout << error.GetMessage() << '\n';
        return 1;
    }

    result = solver.Solve(task, result_tree);

    if (!writer.Write(argv[2], result_tree, error)) {
        std::cout << error.GetMessage() << '\n';
        return 1;
    }

    // std::cout << ResultToText(result) << '\n';
    return 0;
}