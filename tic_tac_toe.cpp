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

bool ParseBoardLines(
    const std::vector<std::string>& lines,
    GameBoard& board,
    Error& error
) {
    // Для каждой из трёх строк поля выполнять
    for (int row = 0; row < BOARD_ROWS; ++row) {
        // Если длина текущей строки не равна 3
        if (lines[row].size() != 3) {
            // Записать сообщение об ошибке размера поля
            error.type = BOARD_SIZE_ERROR;
            error.file_path = "";
            error.row = row + 1;
            error.column = NO_POSITION;
            return false;
        }

        // Для каждого символа текущей строки выполнять
        for (int column = 0; column < BOARD_COLUMNS; ++column) {
            char cell = lines[row][column];

            // если символ не равен X, O и .
            if (cell != 'X' && cell != 'O' && cell != '.') {
                // Записать сообщение об ошибке
                error.type = BOARD_SYMBOL_ERROR;
                error.file_path = "";
                error.row = row + 1;
                error.column = column + 1;
                return false;
            }

            // Сохранить символ в поле
            board.cells[row][column] = cell;
        }
    }

    return true;
}

bool ParsePlayers(
    const std::vector<std::string>& lines,
    StrategyTask& task,
    Error& error
) { 
    // Проверить строку игрока стратегии
    if (!IsCorrectPlayerLine(lines[3])) {
        // Записать сообщение об ошибке
        error.type = STRATEGY_PLAYER_ERROR;
        error.file_path = "";
        error.row = 4;
        error.column = 1;
        return false;
    }

    // Проверить строку игрока следующего хода
    // Если строка игрока следующего хода некорректна
    if (!IsCorrectPlayerLine(lines[4])) {
        // Записать сообщение об ошибке
        error.type = NEXT_PLAYER_ERROR;
        error.file_path = "";
        error.row = 5;
        error.column = 1;
        return false;
    }

    // Сохранить игрока стратегии
    task.strategy_player = lines[3][0];
    // Сохранить игрока следующего хода
    task.next_player = lines[4][0];

    return true;
}

bool IsCorrectPlayerLine(const std::string& line) {
    // Если длина строки не равна 1
    if (line.size() != 1) {
        return false;
    }

    // Если единственный символ строки не равен X и не равен O
    if (line[0] != 'X' && line[0] != 'O') {
        // Вернуть false
        return false;
    }

    return true;
}

bool ValidateCountsAndWins(
    const GameBoard& board,
    Error& error
) {
    // Установить счётчики X и O в ноль
    int x_count = 0;
    int o_count = 0;
    int difference;
    // Установить признаки победы X и O в false
    bool x_wins = false;
    bool o_wins = false;

    // Для каждой клетки поля выполнять
    for (int row = 0; row < BOARD_ROWS; ++row) {
        for (int column = 0; column < BOARD_COLUMNS; ++column) {

            // Если в клетке стоит X - увеличить счётчик X
            if (board.cells[row][column] == 'X') {
                ++x_count;
            }

            // Если в клетке стоит O - увеличить счётчик O
            if (board.cells[row][column] == 'O') {
                ++o_count;
            }
        }
    }

    // Проверить все строки поля
    for (int row = 0; row < BOARD_ROWS; ++row) {
        // Если строка полностью состоит из X
        if (board.cells[row][0] == 'X' &&
            board.cells[row][1] == 'X' &&
            board.cells[row][2] == 'X') {
            // Установить признак победы X
            x_wins = true;
        }

        // Если строка полностью состоит из O
        if (board.cells[row][0] == 'O' &&
            board.cells[row][1] == 'O' &&
            board.cells[row][2] == 'O') {
            // Установить признак победы O
            o_wins = true;
        }
    }

    // Проверить все столбцы поля
    for (int column = 0; column < BOARD_COLUMNS; ++column) {
        // Если столбец полностью состоит из X
        if (board.cells[0][column] == 'X' &&
            board.cells[1][column] == 'X' &&
            board.cells[2][column] == 'X') {
            // Установить признак победы X
            x_wins = true;
        }

        // Если столбец полностью состоит из O
        if (board.cells[0][column] == 'O' &&
            board.cells[1][column] == 'O' &&
            board.cells[2][column] == 'O') {
            // Установить признак победы O
            o_wins = true;
        }
    }

    // Проверить главную диагональ
    if (board.cells[0][0] == 'X' &&
        board.cells[1][1] == 'X' &&
        board.cells[2][2] == 'X') {
        // Установить признак победы
        x_wins = true;
    }

    if (board.cells[0][0] == 'O' &&
        board.cells[1][1] == 'O' &&
        board.cells[2][2] == 'O') {
        // Установить признак победы O
        o_wins = true;
    }

    // Проверить побочную диагональ
    if (board.cells[0][2] == 'X' &&
        board.cells[1][1] == 'X' &&
        board.cells[2][0] == 'X') {
        // Установить признак победы X
        x_wins = true;
    }

    if (board.cells[0][2] == 'O' &&
        board.cells[1][1] == 'O' &&
        board.cells[2][0] == 'O') {
        // Установить признак победы O
        o_wins = true;
    }

    // Вычислить разность между количеством X и O
    difference = x_count - o_count;

    // Если разность меньше -1 или больше 1
    if (difference < -1 || difference > 1) {
        // Записать сообщение об ошибке
        error.type = MARK_COUNT_ERROR;
        error.file_path = "";
        error.row = NO_POSITION;
        error.column = NO_POSITION;
        return false;
    }

    // Если одновременно победили и X, и O
    if (x_wins && o_wins) {
        // Записать сообщение об ошибке
        error.type = BOARD_STATE_ERROR;
        error.file_path = "";
        error.row = NO_POSITION;
        error.column = NO_POSITION;
        return false;
    }

    // Если победил X и количество фигур не соответствует допустимому
    // состоянию
    if (x_wins && !(x_count == o_count || x_count == o_count + 1)) {
        // Записать сообщение об ошибке
        error.type = BOARD_STATE_ERROR;
        error.file_path = "";
        error.row = NO_POSITION;
        error.column = NO_POSITION;
        return false;
    }

    // Если победил O и количество фигур не соответствует допустимому
    // состоянию
    if (o_wins && !(x_count == o_count || o_count == x_count + 1)) {
        // Записать сообщение об ошибке
        error.type = BOARD_STATE_ERROR;
        error.file_path = "";
        error.row = NO_POSITION;
        error.column = NO_POSITION;
        return false;
    }

    return true;
}

bool ValidateNextPlayer(
    const GameBoard& board,
    char next_player,
    Error& error
) {
    // Установить счётчики X и O в ноль
    int x_count = 0;
    int o_count = 0;
    int difference;

    // Для каждой клетки поля выполнять
    for (int row = 0; row < BOARD_ROWS; ++row) {
        for (int column = 0; column < BOARD_COLUMNS; ++column) {
            // Если в клетке стоит X - увеличить счётчик X
            if (board.cells[row][column] == 'X') {
                ++x_count;
            }

            // Если в клетке стоит O - увеличить счётчик O
            if (board.cells[row][column] == 'O') {
                ++o_count;
            }
        }
    }

    // Вычислить разность между количеством X и O
    difference = x_count - o_count;

    // Если разность равна 1 и следующий игрок не равен O
    if (difference == 1 && next_player != 'O') {
        // Записать сообщение об ошибке
        error.type = NEXT_PLAYER_STATE_ERROR;
        error.file_path = "";
        error.row = NO_POSITION;
        error.column = NO_POSITION;
        return false;
    }

    // Если разность равна -1 и следующий игрок не равен X
    if (difference == -1 && next_player != 'X') {
        // Записать сообщение об ошибке
        error.type = NEXT_PLAYER_STATE_ERROR;
        error.file_path = "";
        error.row = NO_POSITION;
        error.column = NO_POSITION;
        return false;
    }

    return true;
}

GameResult TicTacToeSolver::Solve(const StrategyTask& task, TreeNode*& result_tree) { 
    // Рекурсивно оценить позицию
    PositionScore score = EvaluatePosition(task.board, task.next_player, task.strategy_player);
    // Построить оптимальную стратегию
    result_tree = BuildOptimalTree(task.board, task.next_player, task.strategy_player);
    // Вернуть результат оцнеки
    return score.result;
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

GameBoard TicTacToeSolver::MakeMove(
    const GameBoard& board,
    int position,
    char player
) {
    // Создать новое поле.
    GameBoard next_board;
    int row;
    int column;

    // Скопировать в него все клетки исходного поля.
    for (row = 0; row < BOARD_ROWS; ++row) {
        for (column = 0; column < BOARD_COLUMNS; ++column) {
            next_board.cells[row][column] = board.cells[row][column];
        }
    }

    // Вычислить row и column по номеру position.
    row = position / BOARD_COLUMNS;
    column = position % BOARD_COLUMNS;
    // Записать символ player в соответствующую клетку.
    next_board.cells[row][column] = player;

    // Вернуть новое поле
    return next_board;
}

int TicTacToeSolver::CountImmediateWins(const GameBoard& board, char player) {
    // Установить счётчик немедленных побед в ноль.
    int count = 0;

    // Для каждой позиции от 0 до 8 выполнять:
    for (int position = 0; position < BOARD_SIZE; ++position) {
        // Вычислить row и column по номеру позиции.
        int row = position / BOARD_COLUMNS;
        int column = position % BOARD_COLUMNS;

        // Если клетка занята, перейти к следующей позиции.
        if (board.cells[row][column] != '.') {
            continue;
        }

        // Построить новое поле после хода игрока в эту позицию.
        GameBoard next_board = MakeMove(board, position, player);
        // Проверить приводит ли построенное поле к победе игрока
        if (HasWin(next_board, player)) {
            // Если приводит, увеличить счётчик на 1.
            ++count;
        }
    }

    // Вернуть значение счётчика.
    return count;
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

bool TicTacToeSolver::GetTerminalResult(
    const GameBoard& board,
    char strategy_player,
    GameResult& result
) {
    // Проверить победу X
    if (HasWin(board, 'X')) {
        // Если X победил, записать в результат победу или поражение в
        // зависимости от игрока, для которого ищется стратегия
        if (strategy_player == 'X') {
            result = WIN;
        } else {
            result = LOSE;
        }
        return true;
    }

    // Проверить победу O
    if (HasWin(board, 'O')) {
        // Если O победил, записать в результат победу или поражение в
        // зависимости от игрока, для которого ищется стратегия.
        if (strategy_player == 'O') {
            result = WIN;
        } else {
            result = LOSE;
        }
        return true;
    }

    // Если поле заполнено, записать в result ничью
    if (IsBoardFull(board)) {
        result = DRAW;
        return true;
    }

    return false;
}

bool TicTacToeSolver::HasWin(const GameBoard& board, char player) {
    // Проверить все строки поля.
    for (int row = 0; row < BOARD_ROWS; ++row) {
        if (board.cells[row][0] == player &&
            board.cells[row][1] == player &&
            board.cells[row][2] == player) {
            return true;
        }
    }

    // Проверить все столбцы поля.
    for (int column = 0; column < BOARD_COLUMNS; ++column) {
        if (board.cells[0][column] == player &&
            board.cells[1][column] == player &&
            board.cells[2][column] == player) {
            return true;
        }
    }

    // Проверить главную диагональ.
    if (board.cells[0][0] == player &&
        board.cells[1][1] == player &&
        board.cells[2][2] == player) {
        return true;
    }

    // Проверить побочную диагональ.
    if (board.cells[0][2] == player &&
        board.cells[1][1] == player &&
        board.cells[2][0] == player) {
        return true;
    }

    return false;
}

bool TicTacToeSolver::IsBoardFull(const GameBoard& board) {
    // Для каждой клетки поля выполнять
    for (int row = 0; row < BOARD_ROWS; ++row) {
        for (int column = 0; column < BOARD_COLUMNS; ++column) {
            // Если значение клетки = ".", вернуть false.
            if (board.cells[row][column] == '.') {
                return false;
            }
        }
    }

    return true;
}

int TicTacToeSolver::CompareScores(
    const PositionScore& first,
    const PositionScore& second,
    char current_player,
    char strategy_player
) {
    // Определить, совпадает ли текущий игрок с игроком стратегии
    bool strategy_turn = current_player == strategy_player;

    // Если результаты 1 и 2 оценки различаются
    if (first.result != second.result) {
        // Если ходит игрок стратегии
        if (strategy_turn) {
            // Если 1 оценка лучше 2ой, вернуть 1
            if (first.result > second.result) {
                return 1;
            }
            
            return -1;
        }

        // Если 1я оценка хуже для игрока стратегии, чем 2я, вернуть 1
        if (first.result < second.result) {
            return 1;
        }

        return -1;
    }

    // Если результаты равны WIN
    if (first.result == WIN) {
        // Если ходит игрок стратегии и расстояния различаются
        if (strategy_turn && first.distance != second.distance) {
            // Если 1я дистанция меньше 2ой, вернуть 1
            if (first.distance < second.distance) {
                return 1;
            }

            return -1;
        }

        // Если ходит соперник и расстояния различаются
        if (!strategy_turn && first.distance != second.distance) {
            // Если 1я дистанция больше 2ой, вернуть 1
            if (first.distance > second.distance) {
                return 1;
            }

            return -1;
        }
    }

    // Если результаты равны LOSE
    if (first.result == LOSE) {
        // Если ходит игрок стратегии и расстояния различаются
        if (strategy_turn && first.distance != second.distance) {
            // Если 1ая дистанция больше 2ой, вернуть 1
            if (first.distance > second.distance) {
                return 1;
            }

            return -1;
        }

        // Если ходит соперник и расстояния различаются
        if (!strategy_turn && first.distance != second.distance) {
            // Если 1ая дистанция меньше 2ой, вернуть 1
            if (first.distance < second.distance) {
                return 1;
            }

            return -1;
        }
    }

    // Если значения немедленных ходов до победы различаются
    if (first.next_player_win_count != second.next_player_win_count) {
        // Если у 1го значение меньше, вернуть 1
        if (first.next_player_win_count < second.next_player_win_count) {
            return 1;
        }

        return -1;
    }

    return 0;
}

int TicTacToeSolver::CountMark(const GameBoard& board, char mark) {
    // Установить счётчик в ноль.
    int count = 0;

    // Для каждой клетки поля выполнять:
    for (int row = 0; row < BOARD_ROWS; ++row) {
        for (int column = 0; column < BOARD_COLUMNS; ++column) {
            // Проверить, равен ли символ клетки значению mark.
            if (board.cells[row][column] == mark) {
                // Увеличить счётчик на 1.
                ++count;
            }
        }
    }

    // Вернуть значение счётчика.
    return count;
}

char TicTacToeSolver::GetOpponent(char player) {
    // Проверить, равен ли текущий игрок символу X.
    if (player == 'X') {
        // Вернуть O.
        return 'O';
    }

    // Вернуть X.
    return 'X';
}