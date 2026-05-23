#include <vector>
#include "./tic_tac_toe.hpp"
#include <fstream>

bool ParseStrategyTask(
    const std::vector<std::string>& lines,
    StrategyTask& task,
    Error& error
) {
    // Проверить, что входной файл не пуст.
    if (lines.empty()) {
        SetError(error, EMPTY_INPUT_ERROR, "", NO_POSITION, NO_POSITION);
        return false;
    }

    // Проверить, что количество строк не меньше пяти.
    if (lines.size() < TOTAL_INPUT_LINES) {
        SetError(error, MISSING_LINES_ERROR, "", NO_POSITION, NO_POSITION);
        return false;
    }

    // Проверить, что количество строк не больше пяти.
    if (lines.size() > TOTAL_INPUT_LINES) {
        SetError(error, EXTRA_LINES_ERROR, "", NO_POSITION, NO_POSITION);
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
            SetError(error, BOARD_SIZE_ERROR, "", row + 1, NO_POSITION);
            return false;
        }

        // Для каждого символа текущей строки выполнять
        for (int column = 0; column < BOARD_COLUMNS; ++column) {
            char cell = lines[row][column];

            // если символ не равен X, O и .
            if (cell != 'X' && cell != 'O' && cell != '.') {
                // Записать сообщение об ошибке
                SetError(error, BOARD_SYMBOL_ERROR, "", row + 1, column + 1);
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
        SetError(error, STRATEGY_PLAYER_ERROR, "", 4, 1);
        return false;
    }

    // Проверить строку игрока следующего хода
    // Если строка игрока следующего хода некорректна
    if (!IsCorrectPlayerLine(lines[4])) {
        // Записать сообщение об ошибке
        SetError(error, NEXT_PLAYER_ERROR, "", 5, 1);
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
    // Полчситать количество 'X'
    int x_count = CountMark(board, 'X');
    // Полчситать количество 'O'
    int o_count = CountMark(board, 'O');
    int difference;
    // Установить была ли победа X и O
    bool x_wins = HasWin(board, 'X');
    bool o_wins = HasWin(board, 'O');

    // Вычислить разность между количеством X и O
    difference = x_count - o_count;

    // Если разность меньше -1 или больше 1
    if (difference < -1 || difference > 1) {
        // Записать сообщение об ошибке
        SetError(error, MARK_COUNT_ERROR, "", NO_POSITION, NO_POSITION);
        return false;
    }

    // Если одновременно победили и X, и O
    if (x_wins && o_wins) {
        // Записать сообщение об ошибке
        SetError(error, BOARD_STATE_ERROR, "", NO_POSITION, NO_POSITION);
        return false;
    }

    // Если победил X и количество фигур не соответствует допустимому
    // состоянию
    if (x_wins && !(x_count == o_count || x_count == o_count + 1)) {
        // Записать сообщение об ошибке
        SetError(error, BOARD_STATE_ERROR, "", NO_POSITION, NO_POSITION);
        return false;
    }

    // Если победил O и количество фигур не соответствует допустимому
    // состоянию
    if (o_wins && !(x_count == o_count || o_count == x_count + 1)) {
        // Записать сообщение об ошибке
        SetError(error, BOARD_STATE_ERROR, "", NO_POSITION, NO_POSITION);
        return false;
    }

    return true;
}

bool ValidateNextPlayer(
    const GameBoard& board,
    char next_player,
    Error& error
) {
    // Полчситать количество 'X'
    int x_count = CountMark(board, 'X');
    // Полчситать количество 'O'
    int o_count = CountMark(board, 'O');
    int difference;

    // Вычислить разность между количеством X и O
    difference = x_count - o_count;

    // Если разность равна 1 и следующий игрок не равен O
    if (difference == 1 && next_player != 'O') {
        // Записать сообщение об ошибке
        SetError(error, NEXT_PLAYER_STATE_ERROR, "", NO_POSITION, NO_POSITION);
        return false;
    }

    // Если разность равна -1 и следующий игрок не равен X
    if (difference == -1 && next_player != 'X') {
        // Записать сообщение об ошибке
        SetError(error, NEXT_PLAYER_STATE_ERROR, "", NO_POSITION, NO_POSITION);
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

bool HasWin(const GameBoard& board, char player) {
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

int CountMark(const GameBoard& board, char mark) {
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

void DotFileWriter::AssignIds(TreeNode* node, int& next_id) {
    // Записать текущее значение next_id в поле id текущей вершины.
    node->id = next_id;
    // Увеличить значение next id на 1.
    next_id = next_id + 1;

    // Для каждого дочернего узла текущей вершины выполнять:
    for (TreeNode* child : node->children) {
        // Рекурсивно вызвать метод для дочернего узла.
        AssignIds(child, next_id);
    }
}

void DotFileWriter::WriteNodes(std::ostream& output, TreeNode* node) {
    // Начать запись текущей вершины в поток output в формате DOT.
    // Записать имя вершины в виде символа n и значения id текущего узла.
    output << "    n" << node->id << " [label=\"";
    // Записать первую строку поля
    // Записать символ перевода строки в формате \n.
    output << node->board.cells[0][0] << node->board.cells[0][1] << node->board.cells[0][2] << "\\n";
    // Записать вторую строку поля
    // Записать символ перевода строки в формате \n.
    output << node->board.cells[1][0] << node->board.cells[1][1] << node->board.cells[1][2] << "\\n";
    // Записать третью строку поля
    // Записать символ перевода строки в формате \n.
    output << node->board.cells[2][0] << node->board.cells[2][1] << node->board.cells[2][2] << "\"];\n";

    // Для каждого дочернего узла текущей вершины рекурсивно записать
    // вершины графа
    for (TreeNode* child : node->children) {
        WriteNodes(output, child);
    }
}

void DotFileWriter::WriteEdges(std::ostream& output, TreeNode* node) {
    // Для каждого дочернего узла текущей вершины выполнять:
    for (TreeNode* child : node->children) {
        // Записать в поток output ребро от текущей вершины к дочерней
        // вершине в формате DOT.
        output << "    n" << node->id << " -> n" << child->id << ";\n";
        // Рекурсивно вызвать метод для дочернего узла
        WriteEdges(output, child);
    }
}

bool DotFileWriter::Write(
    const std::string& path,
    TreeNode* root,
    Error& error
) {
    std::ofstream output(path);
    int next_id = 0;

    //  Попытаться открыть выходной файл.
    if (!output.is_open()) {
        // Записать сообщение об ошибке доступа к выходному файлу.
        SetError(error, OUTPUT_FILE_ERROR, path, NO_POSITION, NO_POSITION);
        return false;
    }

    // Присвоить вершинам номера
    AssignIds(root, next_id);

    // Записать заголовок графа
    output << "digraph t {\n";
    // Записать все вершины 
    WriteNodes(output, root);
    // Записать все рёбра
    WriteEdges(output, root);
    // Записать закрывающую строку (}.)
    output << "}\n";

    return true;
}

std::string Error::GetMessage() const {
    if (type == INPUT_FILE_ERROR) {
        return "Ошибка доступа к входному файлу";
    }

    if (type == OUTPUT_FILE_ERROR) {
        return "Ошибка доступа к выходному файлу";
    }

    if (type == EMPTY_INPUT_ERROR) {
        return "Пустой входной файл";
    }

    if (type == MISSING_LINES_ERROR) {
        return "Во входном файле отсутствует одна или несколько обязательных строк";
    }

    if (type == EXTRA_LINES_ERROR) {
        return "Во входном файле присутствуют лишние строки";
    }

    if (type == BOARD_SIZE_ERROR) {
        return "Описание игрового поля не соответствует размеру 3x3";
    }

    if (type == BOARD_SYMBOL_ERROR) {
        return "В поле присутствуют символы, отличные от X, O и .";
    }

    if (type == STRATEGY_PLAYER_ERROR) {
        return "Игрок, для которого строится стратегия, задан неверно";
    }

    if (type == NEXT_PLAYER_ERROR) {
        return "Игрок, совершающий следующий ход, задан неверно";
    }

    if (type == MARK_COUNT_ERROR) {
        return "Некорректное соотношение количества X и O";
    }

    if (type == BOARD_STATE_ERROR) {
        return "Состояние игрового поля не соответствует правилам игры";
    }

    if (type == NEXT_PLAYER_STATE_ERROR) {
        return "Указанный игрок, выполняющий следующий ход, не соответствует состоянию поля";
    }

    return "";
}

void SetError(
    Error& error,
    ErrorType type,
    const std::string& file_path,
    int row,
    int column
) {
    error.type = type;
    error.file_path = file_path;
    error.row = row;
    error.column = column;
}