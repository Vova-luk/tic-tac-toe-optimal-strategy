#include <vector>
#include "./tic_tac_toe.hpp"

const int NO_POSITION = -1;
const int TOTAL_INPUT_LINES = 5;

bool ParseStrategyTask(
    const std::vector<std::string>& lines,
    StrategyTask& task,
    Error& error
) {
    // Проверить, что входной файл не пуст.
    if (lines.empty()) {
        error.type = EMPTY_INPUT_ERROR;
        error.file_path = "";
        error.row = NO_POSITION;
        error.column = NO_POSITION;
        return false;
    }

    // Проверить, что количество строк не меньше пяти.
    if (lines.size() < TOTAL_INPUT_LINES) {
        error.type = MISSING_LINES_ERROR;
        error.file_path = "";
        error.row = NO_POSITION;
        error.column = NO_POSITION;
        return false;
    }

    // Проверить, что количество строк не больше пяти.
    if (lines.size() > TOTAL_INPUT_LINES) {
        error.type = EXTRA_LINES_ERROR;
        error.file_path = "";
        error.row = NO_POSITION;
        error.column = NO_POSITION;
        return false;
    }

    //Распарсить поле.
    if (!ParseBoardLines(lines, task.board, error)) {
        return false;
    }

    //Распарсить строки игроков функцией.
    if (!ParsePlayers(lines, task, error)) {
        return false;
    }

    // Проверить корректность количества фигур и побед
    if (!ValidateCountsAndWins(task.board, error)) {
        return false;
    }

    // Проверить корректность следующего игрока
    if (!ValidateNextPlayer(task.board, task.next_player, error)) {
        return false;
    }
    
    // Вернуть true, если все проверки пройдены успешно.
    return true;
}

GameResult TicTacToeSolver::Solve(const StrategyTask& task, TreeNode*& result_tree) { 
    return GameResult{};
}

PositionScore TicTacToeSolver::EvaluatePosition(
        const GameBoard& board,
        char current_player,
        char strategy_player
    ) {
        return PositionScore{};
    }

PositionScore TicTacToeSolver::EvaluateMove(
        const GameBoard& board,
        int position,
        char current_player,
        char strategy_player
    ) {
        return PositionScore{};
    }

TreeNode* TicTacToeSolver::BuildOptimalTree(
        const GameBoard& board,
        char current_player,
        char strategy_player
    ) {
    TreeNode* node = new TreeNode();

    return node;
    }