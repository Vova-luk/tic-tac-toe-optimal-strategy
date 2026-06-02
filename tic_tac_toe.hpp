/**
 * @file tic_tac_toe.hpp
 * @brief Публичный интерфейс решателя оптимальной стратегии для игры
 *        "крестики-нолики".
 *
 * @mainpage TicTacToe Strategy Solver
 *
 * Программа читает позицию игры из текстового файла, вычисляет оптимальную
 * стратегию для выбранного игрока и сохраняет дерево оптимальных продолжений
 * в формате DOT.
 *
 * @section mainpage_input Входные данные
 * Входной файл должен содержать ровно пять строк:
 * - первые три строки задают игровое поле размером 3x3;
 * - четвертая строка задает игрока, для которого строится стратегия;
 * - пятая строка задает игрока следующего хода.
 *
 * Допустимые символы поля: `X`, `O` и `.`.
 *
 * @section mainpage_output Выходные данные
 * Программа создает DOT-файл, который описывает дерево всех оптимальных
 * продолжений из исходной позиции.
 *
 * @section mainpage_docs Документация
 * Doxygen-документация включает описание структур данных, перечислений,
 * свободных функций и методов классов проекта.
 */

#ifndef TIC_TAC_TOE_HPP
#define TIC_TAC_TOE_HPP

#include <cstddef>
#include <iosfwd>
#include <string>
#include <vector>

/**
 * @brief Значение, обозначающее отсутствие позиции строки или столбца.
 */
const int NO_POSITION = -1;

/**
 * @brief Обязательное количество строк во входном файле.
 *
 * Первые три строки задают поле, четвертая строка задает игрока стратегии,
 * пятая строка задает игрока следующего хода.
 */
const int TOTAL_INPUT_LINES = 5;

/**
 * @brief Количество строк игрового поля.
 */
const int BOARD_ROWS = 3;

/**
 * @brief Количество столбцов игрового поля.
 */
const int BOARD_COLUMNS = 3;

/**
 * @brief Общее количество клеток игрового поля.
 */
const int BOARD_SIZE = 9;

/**
 * @brief Максимальное количество строк, которое требуется считать из файла.
 */
const std::size_t MAX_READABLE_LINES = 6;

/**
 * @brief Результат игры для игрока, для которого строится стратегия.
 */
enum GameResult {
    LOSE = -1,  ///< Игрок стратегии проигрывает при оптимальной игре.
    DRAW = 0,   ///< Партия заканчивается вничью при оптимальной игре.
    WIN = 1     ///< Игрок стратегии выигрывает при оптимальной игре.
};

/**
 * @brief Тип ошибки, возникающей при чтении, проверке данных или записи результата.
 */
enum ErrorType {
    NO_ERROR = 0,              ///< Ошибка отсутствует.
    INPUT_FILE_ERROR,          ///< Не удалось открыть входной файл.
    OUTPUT_FILE_ERROR,         ///< Не удалось записать выходной файл.
    EMPTY_INPUT_ERROR,         ///< Входной файл пуст.
    MISSING_LINES_ERROR,       ///< Во входном файле меньше пяти строк.
    EXTRA_LINES_ERROR,         ///< Во входном файле больше пяти строк.
    BOARD_SIZE_ERROR,          ///< Строка поля имеет неверную длину.
    BOARD_SYMBOL_ERROR,        ///< В поле найден недопустимый символ.
    STRATEGY_PLAYER_ERROR,     ///< Некорректно задан игрок стратегии.
    NEXT_PLAYER_ERROR,         ///< Некорректно задан игрок следующего хода.
    MARK_COUNT_ERROR,          ///< Количество X и O не соответствует правилам.
    BOARD_STATE_ERROR,         ///< Состояние поля невозможно в реальной игре.
    NEXT_PLAYER_STATE_ERROR    ///< Следующий игрок не соответствует позиции.
};

/**
 * @brief Информация об ошибке.
 *
 * Структура хранит тип ошибки, путь к файлу, а также позицию ошибки
 * во входных данных, если строка и столбец могут быть определены.
 */
struct Error {
    ErrorType type;        ///< Тип обнаруженной ошибки.
    std::string file_path; ///< Путь к файлу, связанному с ошибкой.
    int row;               ///< Номер строки ошибки или `NO_POSITION`.
    int column;            ///< Номер столбца ошибки или `NO_POSITION`.

    /**
     * @brief Формирует текстовое сообщение об ошибке.
     *
     * @return Строка с описанием ошибки для вывода пользователю.
     */
    std::string GetMessage() const;
};

/**
 * @brief Игровое поле крестиков-ноликов.
 *
 * Поле имеет размер 3x3. Каждая клетка может содержать символ:
 * 'X', 'O' или '.'.
 */
struct GameBoard {
    char cells[3][3]; ///< Клетки поля: `X`, `O` или `.`.
};

/**
 * @brief Входная задача для поиска оптимальной стратегии.
 */
struct StrategyTask {
    GameBoard board;      ///< Исходное состояние игрового поля.
    char strategy_player; ///< Игрок, для которого строится стратегия.
    char next_player;     ///< Игрок, который должен ходить следующим.
};

/**
 * @brief Вершина дерева оптимальной стратегии.
 *
 * Каждая вершина хранит состояние поля и список оптимальных продолжений
 * из данной позиции.
 */
struct TreeNode {
    int id;                         ///< Идентификатор вершины в DOT-графе.
    GameBoard board;                ///< Позиция, соответствующая вершине.
    std::vector<TreeNode*> children; ///< Оптимальные дочерние продолжения.
};

/**
 * @brief Оценка игровой позиции.
 *
 * Используется при выборе оптимального хода с учетом результата,
 * расстояния до конечного исхода и количества немедленных побед
 * у следующего игрока.
 */
struct PositionScore {
    GameResult result;          ///< Ожидаемый итог партии.
    int distance;               ///< Число ходов до конечного результата.
    int next_player_win_count;  ///< Количество немедленных победных ходов.
};

/**
 * @brief Класс для вычисления оптимальной стратегии в крестиках-ноликах.
 *
 * Класс рекурсивно оценивает позиции игры, выбирает оптимальные ходы
 * и строит дерево только оптимальных продолжений.
 */
class TicTacToeSolver {
public:
    /**
     * @brief Вычисляет гарантированный результат и строит дерево стратегии.
     *
     * @param[in] task Проверенные входные данные: поле, игрок стратегии
     *                 и игрок следующего хода.
     * @param[out] result_tree Указатель, в который будет записан корень дерева
     *                         оптимальной стратегии.
     * @return Итоговый гарантированный результат для игрока стратегии.
     */
    GameResult Solve(const StrategyTask& task, TreeNode*& result_tree);

    /**
     * @brief Рекурсивно оценивает игровую позицию.
     *
     * Метод перебирает все возможные ходы из текущей позиции и выбирает
     * лучшую оценку с учетом того, кто ходит: игрок стратегии или соперник.
     *
     * @param[in] board Текущее состояние игрового поля.
     * @param[in] current_player Игрок, который должен сделать ход.
     * @param[in] strategy_player Игрок, для которого строится стратегия.
     * @return Оценка текущей позиции.
     */
    PositionScore EvaluatePosition(
        const GameBoard& board,
        char current_player,
        char strategy_player
    );

    /**
     * @brief Оценивает один возможный ход.
     *
     * Метод строит новое поле после хода, рекурсивно оценивает полученную
     * позицию и обновляет расстояние до результата.
     *
     * @param[in] board Текущее состояние игрового поля.
     * @param[in] position Номер клетки для хода от 0 до 8.
     * @param[in] current_player Игрок, который выполняет ход.
     * @param[in] strategy_player Игрок, для которого строится стратегия.
     * @return Оценка позиции после выбранного хода.
     */
    PositionScore EvaluateMove(
        const GameBoard& board,
        int position,
        char current_player,
        char strategy_player
    );

    /**
     * @brief Строит дерево только оптимальных продолжений.
     *
     * Если из позиции существует несколько равнозначных оптимальных ходов,
     * все такие ходы добавляются в дерево.
     *
     * @param[in] board Текущее состояние игрового поля.
     * @param[in] current_player Игрок, который должен сделать ход.
     * @param[in] strategy_player Игрок, для которого строится стратегия.
     * @return Указатель на корень построенного поддерева.
     */
    TreeNode* BuildOptimalTree(
        const GameBoard& board,
        char current_player,
        char strategy_player
    );

private:
    /**
     * @brief Возвращает соперника указанного игрока.
     *
     * @param[in] player Текущий игрок: 'X' или 'O'.
     * @return Символ другого игрока.
     */
    char GetOpponent(char player);

    /**
     * @brief Проверяет, заполнено ли игровое поле.
     *
     * @param[in] board Текущее состояние игрового поля.
     * @return true, если на поле нет пустых клеток.
     * @return false, если хотя бы одна клетка содержит '.'.
     */
    bool IsBoardFull(const GameBoard& board);

    /**
     * @brief Подсчитывает количество ходов, которые сразу приводят к победе.
     *
     * @param[in] board Текущее состояние игрового поля.
     * @param[in] player Игрок, для которого выполняется подсчет.
     * @return Количество немедленных победных ходов.
     */
    int CountImmediateWins(const GameBoard& board, char player);

    /**
     * @brief Определяет, является ли позиция конечной.
     *
     * Позиция считается конечной, если один из игроков победил
     * или игровое поле полностью заполнено.
     *
     * @param[in] board Текущее состояние игрового поля.
     * @param[in] strategy_player Игрок, для которого строится стратегия.
     * @param[out] result Переменная для записи результата конечной позиции.
     * @return true, если позиция конечная.
     * @return false, если игра может быть продолжена.
     */
    bool GetTerminalResult(
        const GameBoard& board,
        char strategy_player,
        GameResult& result
    );

    /**
     * @brief Создает новое поле после выполнения хода.
     *
     * Исходное поле не изменяется. Метод копирует его и ставит символ
     * игрока в выбранную клетку.
     *
     * @param[in] board Текущее состояние игрового поля.
     * @param[in] position Номер клетки от 0 до 8.
     * @param[in] player Игрок, выполняющий ход.
     * @return Новое состояние поля после хода.
     */
    GameBoard MakeMove(const GameBoard& board, int position, char player);

    /**
     * @brief Сравнивает две оценки позиции.
     *
     * Метод учитывает результат игры, расстояние до результата,
     * текущего игрока и количество немедленных побед у следующего игрока.
     *
     * @param[in] first Первая оценка.
     * @param[in] second Вторая оценка.
     * @param[in] current_player Игрок, который выбирает ход.
     * @param[in] strategy_player Игрок, для которого строится стратегия.
     * @return 1, если первая оценка лучше.
     * @return 0, если оценки равны.
     * @return -1, если первая оценка хуже.
     */
    int CompareScores(
        const PositionScore& first,
        const PositionScore& second,
        char current_player,
        char strategy_player
    );
};

/**
 * @brief Класс для записи дерева оптимальной стратегии в DOT-файл.
 */
class DotFileWriter {
public:
    /**
     * @brief Записывает дерево стратегии в файл формата DOT.
     *
     * Метод открывает выходной файл, нумерует вершины дерева,
     * записывает вершины и ребра графа.
     *
     * @param[in] path Путь к выходному DOT-файлу.
     * @param[in,out] root Корень дерева оптимальной стратегии.
     * @param[out] error Структура для записи информации об ошибке.
     * @return true, если файл успешно записан.
     * @return false, если произошла ошибка записи.
     */
    bool Write(
        const std::string& path,
        TreeNode* root,
        Error& error
    );

private:
    /**
     * @brief Присваивает вершинам дерева уникальные номера.
     *
     * @param[in,out] node Текущая вершина дерева.
     * @param[in,out] next_id Следующий свободный номер вершины.
     */
    void AssignIds(TreeNode* node, int& next_id);

    /**
     * @brief Записывает вершины дерева в DOT-файл.
     *
     * @param[in,out] output Поток записи в выходной файл.
     * @param[in] node Текущая вершина дерева.
     */
    void WriteNodes(std::ostream& output, const TreeNode* node);

    /**
     * @brief Записывает ребра дерева в DOT-файл.
     *
     * @param[in,out] output Поток записи в выходной файл.
     * @param[in] node Текущая вершина дерева.
     */
    void WriteEdges(std::ostream& output, const TreeNode* node);
};

/**
 * @brief Освобождает память, занятую деревом стратегии.
 *
 * Рекурсивно удаляет дочерние вершины, а затем текущую вершину.
 *
 * @param[in] node Корень дерева или поддерева.
 */
void DeleteTree(TreeNode* node);

/**
 * @brief Проверяет корректность строки с обозначением игрока.
 *
 * Корректная строка должна состоять ровно из одного символа:
 * 'X' или 'O'.
 *
 * @param[in] line Строка из входного файла.
 * @return true, если строка корректна.
 * @return false, если строка задана неверно.
 */
bool IsCorrectPlayerLine(const std::string& line);

/**
 * @brief Разбирает первые три строки входного файла как игровое поле.
 *
 * Каждая строка поля должна иметь длину 3 и содержать только символы
 * 'X', 'O' или '.'.
 *
 * @param[in] lines Строки входного файла.
 * @param[out] board Структура, в которую записывается поле.
 * @param[out] error Структура для записи информации об ошибке.
 * @return true, если поле корректно.
 * @return false, если формат поля нарушен.
 */
bool ParseBoardLines(
    const std::vector<std::string>& lines,
    GameBoard& board,
    Error& error
);

/**
 * @brief Разбирает строки с игроком стратегии и игроком следующего хода.
 *
 * Четвертая строка входного файла задает игрока стратегии,
 * пятая строка задает игрока следующего хода.
 *
 * @param[in] lines Строки входного файла.
 * @param[out] task Структура задачи, в которую записываются игроки.
 * @param[out] error Структура для записи информации об ошибке.
 * @return true, если строки игроков корректны.
 * @return false, если хотя бы один игрок задан неверно.
 */
bool ParsePlayers(
    const std::vector<std::string>& lines,
    StrategyTask& task,
    Error& error
);

/**
 * @brief Проверяет корректность количества фигур и выигрышных линий.
 *
 * Метод проверяет соотношение количества X и O, а также невозможность
 * одновременной победы двух игроков.
 *
 * @param[in] board Текущее состояние игрового поля.
 * @param[out] error Структура для записи информации об ошибке.
 * @return true, если состояние поля соответствует правилам игры.
 * @return false, если состояние поля некорректно.
 */
bool ValidateCountsAndWins(
    const GameBoard& board,
    Error& error
);

/**
 * @brief Проверяет соответствие следующего игрока состоянию поля.
 *
 * Следующий игрок должен соответствовать количеству уже сделанных ходов.
 *
 * @param[in] board Текущее состояние игрового поля.
 * @param[in] next_player Игрок, который должен сделать следующий ход.
 * @param[out] error Структура для записи информации об ошибке.
 * @return true, если следующий игрок указан корректно.
 * @return false, если следующий игрок не соответствует состоянию поля.
 */
bool ValidateNextPlayer(
    const GameBoard& board,
    char next_player,
    Error& error
);

/**
 * @brief Полностью разбирает и проверяет входные данные.
 *
 * Метод проверяет количество строк, разбирает поле, разбирает игроков,
 * проверяет количество фигур, победные линии и следующего игрока.
 *
 * @param[in] lines Строки входного файла.
 * @param[out] task Структура для записи проверенных входных данных.
 * @param[out] error Структура для записи информации об ошибке.
 * @return true, если входные данные корректны.
 * @return false, если найдена ошибка.
 */
bool ParseStrategyTask(
    const std::vector<std::string>& lines,
    StrategyTask& task,
    Error& error
);

/**
 * @brief Преобразует результат игры в текстовое представление.
 *
 * @param[in] result Результат игры для игрока стратегии.
 * @return Строка с текстовым описанием результата.
 */
std::string ResultToText(GameResult result);

/**
 * @brief Заполняет структуру ошибки переданными значениями.
 *
 * @param[out] error Структура ошибки, которую нужно заполнить.
 * @param[in] type Тип ошибки.
 * @param[in] file_path Путь к файлу, если ошибка связана с файлом.
 * @param[in] row Номер строки ошибки или NO_POSITION.
 * @param[in] column Номер столбца ошибки или NO_POSITION.
 */
void SetError(
    Error& error,
    ErrorType type,
    const std::string& file_path = "",
    int row = NO_POSITION,
    int column = NO_POSITION
);

/**
 * @brief Подсчитывает количество заданных символов на поле.
 *
 * @param[in] board Текущее состояние игрового поля.
 * @param[in] mark Символ, который нужно подсчитать.
 * @return Количество вхождений символа mark на поле.
 */
int CountMark(const GameBoard& board, char mark);

/**
 * @brief Проверяет наличие выигрышной линии у игрока.
 *
 * Проверяются все строки, все столбцы, главная и побочная диагонали.
 *
 * @param[in] board Текущее состояние игрового поля.
 * @param[in] player Игрок, для которого выполняется проверка.
 * @return true, если у игрока есть выигрышная линия.
 * @return false, если выигрышной линии нет.
 */
bool HasWin(const GameBoard& board, char player);

/**
 * @brief Считывает строки входного файла для последующего разбора позиции.
 *
 * Функция читает не более `MAX_READABLE_LINES` строк и удаляет завершающий
 * символ `\r`, если файл использует окончания строк Windows.
 *
 * @param[in] path Путь к входному текстовому файлу.
 * @param[out] lines Считанные строки входного файла.
 * @param[out] error Структура для записи информации об ошибке открытия файла.
 * @return true, если файл успешно прочитан.
 * @return false, если файл не удалось открыть.
 */
bool ReadInputFile(
    const std::string& path,
    std::vector<std::string>& lines,
    Error& error
);

int CompareDistance(const PositionScore& first, const PositionScore& second, bool strategy_turn);

int CompareByPreference(int first, int second, bool prefer_greater);

#endif