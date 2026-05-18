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
    // Построить новое поле после хода текущего игрока (MakeMove).
    GameBoard next_board = MakeMove(board, position, current_player);
    // Определить следующего игрока
    char opponent = GetOpponent(current_player);
    // Рекурсивно оценить новую позицию и получить оценку позиции
    PositionScore score =
        EvaluatePosition(next_board, opponent, strategy_player);

    // Увеличить расстояние до результата на 1
    score.distance = score.distance + 1; 
    // Подсчитать количество немедленных побед у следующего игрока
    score.next_player_win_count =
        CountImmediateWins(next_board, GetOpponent(current_player));

    return score;
    }

TreeNode* TicTacToeSolver::BuildOptimalTree(
        const GameBoard& board,
        char current_player,
        char strategy_player
    ) {
    // Создать новый узел дерева
    TreeNode* root = new TreeNode();

    GameResult terminal_result;
    PositionScore best_score;
    bool has_best = false;

    root->id = 0;
    // Записать в узел текущее поле
    root->board = board;
    // Проверить, является ли позиция конечной.
    if (GetTerminalResult(board, strategy_player, terminal_result)) {
        // Вернуть узел без потомков
        return root;
    }

    // Для каждой позиции от 0 до 8 выполнять
    for (int position = 0; position < BOARD_SIZE; ++position) {
        // Вычислить строку и столбец по номеру позиции
        int row = position / BOARD_COLUMNS;
        int column = position % BOARD_COLUMNS;
        PositionScore current_score;

        // Если клетка занята
        if (board.cells[row][column] != '.') {
            // Перейти к следующей позиции
            continue;
        }

        // Вычислить оценку хода.
        current_score = EvaluateMove(board, position, current_player, strategy_player);

        // Если лучшая оценка отсутствует
        if (!has_best) {
            // Сохранить текущую оценку как лучшую
            best_score = current_score;
            // Установить признак наличия лучшей оценки
            has_best = true;
        // Иначе сравнить текущую оценку с лучшей
        } else if (CompareScores(current_score, best_score, current_player, strategy_player) > 0) {
            // Заменить лучшую оценку
            best_score = current_score;
        }
    }

    // Для каждой позиции от 0 до 8 выполнять
    for (int position = 0; position < BOARD_SIZE; ++position) {
        // Вычислить строку и столбец по номеру позиции
        int row = position / BOARD_COLUMNS;
        int column = position % BOARD_COLUMNS;
        PositionScore current_score;
        GameBoard next_board;
        TreeNode* child;

        // Если клетка занята
        if (board.cells[row][column] != '.') {
            // Перейти к следующей позиции
            continue;
        }

        // Повторно вычислить оценку хода
        current_score = EvaluateMove(board, position, current_player, strategy_player);

        // Сравнить её с лучшей оценкой
        if (CompareScores(current_score, best_score, current_player, strategy_player) == 0) {
            // Если оценки равны
            // Построить новое поле
            next_board = MakeMove(board, position, current_player);
            // Рекурсивно построить дочернее поддерево
            child = BuildOptimalTree(next_board, GetOpponent(current_player), strategy_player);
            // Добавить дочерний узел в список children
            root->children.push_back(child);
        }
    }
    // Вернуть указатель на текущий узел
    return root;
    }