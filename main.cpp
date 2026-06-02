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

    // Проверить, удалось ли открыть входной файл.
    if (!input.is_open()) {
        // Записать ошибку
        error.type = INPUT_FILE_ERROR;
        error.file_path = path;
        error.row = NO_POSITION;
        error.column = NO_POSITION;
        return false;
    }

    // Очистить вектор перед чтением нового файла.
    lines.clear();

    // Считать строки файла, но не больше допустимого лимита.
    while (std::getline(input, line)) {
        // Удалить '\r'
        if (!line.empty() && line[line.size() - 1] == '\r') {
            line.erase(line.size() - 1);
        }

        lines.push_back(line);

        // Eсли достигнут максимум читаемых строк.
        if (lines.size() >= MAX_READABLE_LINES) {
            // Прекратить чтение
            break;
        }
    }

    return true;
}

/**
 * @brief Запускает консольное приложение.
 *
 * Программа ожидает два аргумента командной строки: путь к входному файлу
 * с позицией и путь к выходному DOT-файлу для дерева оптимальной стратегии.
 *
 * @param[in] argc Количество аргументов командной строки.
 * @param[in] argv Массив аргументов командной строки.
 * @return `0`, если программа успешно завершилась.
 * @return Ненулевой код, если произошла ошибка чтения, проверки или записи.
 */
int main(int argc, char* argv[]) {
    std::vector<std::string> lines;
    StrategyTask task;
    Error error;
    TicTacToeSolver solver;
    DotFileWriter writer;
    TreeNode* result_tree = 0;
    GameResult result;

    // Инициализировать структуру ошибки.
    error.type = NO_ERROR;
    error.file_path = "";
    error.row = NO_POSITION;
    error.column = NO_POSITION;

    // Проверить корректность аргументов командной строки.
    if (argc != 3) {
        // Вывести ошибку
        std::cout << "Использование: " << argv[0] << " <input.txt> <output.dot>\n";
        return 1;
    }

    // Считать входные данные из файла.
    if (!ReadInputFile(argv[1], lines, error)) {
        // Вывести ошибку
        std::cout << error.GetMessage() << '\n';
        return 1;
    }

    // Разобрать и проверить входную позицию.
    if (!ParseStrategyTask(lines, task, error)) {
        // Вывести ошибку
        std::cout << error.GetMessage() << '\n';
        return 1;
    }

    // Построить оптимальную стратегию для переданной позиции.
    result = solver.Solve(task, result_tree);

    // Сохранить построенное дерево в выходной DOT-файл.
    if (!writer.Write(argv[2], result_tree, error)) {
        // Вывести ошибку
        std::cout << error.GetMessage() << '\n';
        return 1;
    }
    return 0;
}