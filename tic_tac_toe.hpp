#ifndef TIC_TAC_TOE_HPP
#define TIC_TAC_TOE_HPP

#include <iosfwd>
#include <string>
#include <vector>

const int NO_POSITION = -1;
const int TOTAL_INPUT_LINES = 5;
const int BOARD_ROWS = 3;
const int BOARD_COLUMNS = 3;
const int BOARD_SIZE = 9;
const std::size_t MAX_READABLE_LINES = 6;

enum GameResult {
    LOSE = -1,
    DRAW = 0,
    WIN = 1
};

enum ErrorType {
    NO_ERROR = 0,
    INPUT_FILE_ERROR,
    OUTPUT_FILE_ERROR,
    EMPTY_INPUT_ERROR,
    MISSING_LINES_ERROR,
    EXTRA_LINES_ERROR,
    BOARD_SIZE_ERROR,
    BOARD_SYMBOL_ERROR,
    STRATEGY_PLAYER_ERROR,
    NEXT_PLAYER_ERROR,
    MARK_COUNT_ERROR,
    BOARD_STATE_ERROR,
    NEXT_PLAYER_STATE_ERROR
};

struct Error {
    ErrorType type;
    std::string file_path;
    int row;
    int column;

    std::string GetMessage() const;
};

struct GameBoard {
    char cells[3][3];
};

struct StrategyTask {
    GameBoard board;
    char strategy_player;
    char next_player;
};

struct TreeNode {
    int id;
    GameBoard board;
    std::vector<TreeNode*> children;
};

struct PositionScore {
    GameResult result;
    int distance;
    int next_player_win_count;
};

class TicTacToeSolver {
public:
    GameResult Solve(const StrategyTask& task, TreeNode*& result_tree);

    PositionScore EvaluatePosition(
        const GameBoard& board,
        char current_player,
        char strategy_player
    );

    PositionScore EvaluateMove(
        const GameBoard& board,
        int position,
        char current_player,
        char strategy_player
    );

    TreeNode* BuildOptimalTree(
        const GameBoard& board,
        char current_player,
        char strategy_player
    );

private:
    char GetOpponent(char player);
    int CountMark(const GameBoard& board, char mark);
    bool HasWin(const GameBoard& board, char player);
    bool IsBoardFull(const GameBoard& board);
    int CountImmediateWins(const GameBoard& board, char player);

    bool GetTerminalResult(
        const GameBoard& board,
        char strategy_player,
        GameResult& result
    );

    GameBoard MakeMove(const GameBoard& board, int position, char player);

    int CompareScores(
        const PositionScore& first,
        const PositionScore& second,
        char current_player,
        char strategy_player
    );
};

class DotFileWriter {
public:
    bool Write(
        const std::string& path,
        TreeNode* root,
        Error& error
    );

private:
    void AssignIds(TreeNode* node, int& next_id);
    void WriteNodes(std::ostream& output, TreeNode* node);
    void WriteEdges(std::ostream& output, TreeNode* node);
};

void DeleteTree(TreeNode* node);

bool IsCorrectPlayerLine(const std::string& line);

bool ParseBoardLines(
    const std::vector<std::string>& lines,
    GameBoard& board,
    Error& error
);

bool ParsePlayers(
    const std::vector<std::string>& lines,
    StrategyTask& task,
    Error& error
);

bool ValidateCountsAndWins(
    const GameBoard& board,
    Error& error
);

bool ValidateNextPlayer(
    const GameBoard& board,
    char next_player,
    Error& error
);

bool ParseStrategyTask(
    const std::vector<std::string>& lines,
    StrategyTask& task,
    Error& error
);

std::string ResultToText(GameResult result);

#endif
