#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "../tic_tac_toe.hpp"

namespace
{
    using Lines = std::vector<std::string>;
    using Board = std::vector<std::string>;

    void ExpectBoardEq(const GameBoard& actual, const Board& expected)
    {
        ASSERT_EQ(expected.size(), 3u);

        for (int row = 0; row < 3; ++row)
        {
            ASSERT_EQ(expected[row].size(), 3u);

            for (int column = 0; column < 3; ++column)
            {
                EXPECT_EQ(actual.cells[row][column], expected[row][column])
                    << "row = " << row + 1
                    << ", column = " << column + 1;
            }
        }
    }

    void ExpectValidTask(
        const StrategyTask& task,
        const Board& expectedBoard,
        char expectedStrategyPlayer,
        char expectedNextPlayer)
    {
        ExpectBoardEq(task.board, expectedBoard);
        EXPECT_EQ(task.strategy_player, expectedStrategyPlayer);
        EXPECT_EQ(task.next_player, expectedNextPlayer);
    }
}

// №1
TEST(ParseStrategyTaskTests, ValidEmptyBoard)
{
    Lines lines = {
        "...",
        "...",
        "...",
        "O",
        "X"
    };

    StrategyTask task{};
    Error error{};

    bool result = ParseStrategyTask(lines, task, error);

    EXPECT_TRUE(result);
    // ExpectValidTask(task, {"...", "...", "..."}, 'O', 'X');
    // EXPECT_EQ(error.type, NO_ERROR);
}

// №2
TEST(ParseStrategyTaskTests, ValidNextMoveByO)
{
    Lines lines = {
        "X..",
        "...",
        "...",
        "X",
        "O"
    };

    StrategyTask task{};
    Error error{};

    bool result = ParseStrategyTask(lines, task, error);

    EXPECT_TRUE(result);
    ExpectValidTask(task, {"X..", "...", "..."}, 'X', 'O');
    EXPECT_EQ(error.type, NO_ERROR);
}

// №3
TEST(ParseStrategyTaskTests, ValidBoardWhereXAlreadyWon)
{
    Lines lines = {
        "XXX",
        "OO.",
        "...",
        "X",
        "O"
    };

    StrategyTask task{};
    Error error{};

    bool result = ParseStrategyTask(lines, task, error);

    EXPECT_TRUE(result);
    ExpectValidTask(task, {"XXX", "OO.", "..."}, 'X', 'O');
    EXPECT_EQ(error.type, NO_ERROR);
}

// №5
TEST(ParseStrategyTaskTests, EmptyInputFile)
{
    Lines lines = {};

    StrategyTask task{};
    Error error{};

    bool result = ParseStrategyTask(lines, task, error);

    EXPECT_FALSE(result);
    EXPECT_EQ(error.type, EMPTY_INPUT_ERROR);
}

// №6
TEST(ParseStrategyTaskTests, MissingRequiredLine)
{
    Lines lines = {
        "...",
        "...",
        "...",
        "X"
    };

    StrategyTask task{};
    Error error{};

    bool result = ParseStrategyTask(lines, task, error);

    EXPECT_FALSE(result);
    EXPECT_EQ(error.type, MISSING_LINES_ERROR);
}

// №7
TEST(ParseStrategyTaskTests, ExtraLines)
{
    Lines lines = {
        "...",
        "...",
        "...",
        "X",
        "X",
        "O"
    };

    StrategyTask task{};
    Error error{};

    bool result = ParseStrategyTask(lines, task, error);

    EXPECT_FALSE(result);
    EXPECT_EQ(error.type, EXTRA_LINES_ERROR);
}

// №8
TEST(ParseStrategyTaskTests, InvalidBoardSize)
{
    Lines lines = {
        "....",
        "...",
        "...",
        "X",
        "X"
    };

    StrategyTask task{};
    Error error{};

    bool result = ParseStrategyTask(lines, task, error);

    EXPECT_FALSE(result);
    EXPECT_EQ(error.type, BOARD_SIZE_ERROR);
    EXPECT_EQ(error.row, 1);
}

// №9
TEST(ParseStrategyTaskTests, InvalidBoardSymbol)
{
    Lines lines = {
        ".Y.",
        "...",
        "...",
        "X",
        "X"
    };

    StrategyTask task{};
    Error error{};

    bool result = ParseStrategyTask(lines, task, error);

    EXPECT_FALSE(result);
    EXPECT_EQ(error.type, BOARD_SYMBOL_ERROR);
    EXPECT_EQ(error.row, 1);
    EXPECT_EQ(error.column, 2);
}

// №10
TEST(ParseStrategyTaskTests, InvalidStrategyPlayer)
{
    Lines lines = {
        "...",
        "...",
        "...",
        "Y",
        "X"
    };

    StrategyTask task{};
    Error error{};

    bool result = ParseStrategyTask(lines, task, error);

    EXPECT_FALSE(result);
    EXPECT_EQ(error.type, STRATEGY_PLAYER_ERROR);
    EXPECT_EQ(error.row, 4);
}

// №11
TEST(ParseStrategyTaskTests, InvalidNextPlayer)
{
    Lines lines = {
        "...",
        "...",
        "...",
        "X",
        "Y"
    };

    StrategyTask task{};
    Error error{};

    bool result = ParseStrategyTask(lines, task, error);

    EXPECT_FALSE(result);
    EXPECT_EQ(error.type, NEXT_PLAYER_ERROR);
    EXPECT_EQ(error.row, 5);
}

// №12
TEST(ParseStrategyTaskTests, TooManyXMarks)
{
    Lines lines = {
        "XX.",
        "X..",
        "...",
        "X",
        "O"
    };

    StrategyTask task{};
    Error error{};

    bool result = ParseStrategyTask(lines, task, error);

    EXPECT_FALSE(result);
    EXPECT_EQ(error.type, MARK_COUNT_ERROR);
}

// №13
TEST(ParseStrategyTaskTests, BothPlayersWon)
{
    Lines lines = {
        "XXX",
        "OOO",
        "...",
        "X",
        "X"
    };

    StrategyTask task{};
    Error error{};

    bool result = ParseStrategyTask(lines, task, error);

    EXPECT_FALSE(result);
    EXPECT_EQ(error.type, BOARD_STATE_ERROR);
}

// №15
TEST(ParseStrategyTaskTests, InvalidNextPlayerWhenXHasOneMoreMove)
{
    Lines lines = {
        "X..",
        "...",
        "...",
        "O",
        "X"
    };

    StrategyTask task{};
    Error error{};

    bool result = ParseStrategyTask(lines, task, error);

    EXPECT_FALSE(result);
    EXPECT_EQ(error.type, NEXT_PLAYER_STATE_ERROR);
}