#include <vector>
#include "./tic_tac_toe.hpp"

const int NO_POSITION = -1;
const int TOTAL_INPUT_LINES = 5;
const int BOARD_ROWS = 3;
const int BOARD_COLUMNS = 3;
const int BOARD_SIZE = 9;

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
        GameResult terminal_result;
        PositionScore best_score;

        // Проверить, является ли позиция конечной.
        if (GetTerminalResult(board, strategy_player, terminal_result)) {
            // Вернуть позицию как конечный результат
            best_score.result = terminal_result;
            best_score.distance = 0;
            best_score.next_player_win_count = 0;
            return best_score;
        }

        // Считать отсутствие лучшей оценки.
        bool has_best = false;

        // Для каждой клетки поля выполнять
        for (int position = 0; position < BOARD_SIZE; ++position) {
            int row = position / BOARD_COLUMNS;
            int column = position % BOARD_COLUMNS;
            PositionScore current_score;

            // Проверить, свободна ли клетка.
            if (board.cells[row][column] != '.') {
                continue;
            }

            // Оценить ход в эту клетку
            current_score = EvaluateMove(board, position, current_player, strategy_player);

            // Если лучшая оценка ещё не выбрана, то
            if (!has_best) {
                best_score = current_score;
                has_best = true;
            } else if (CompareScores(current_score, best_score, current_player, strategy_player) > 0) {
                best_score = current_score;
            }
    }

    return best_score;
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