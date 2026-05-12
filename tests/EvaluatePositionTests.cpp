#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "../tic_tac_toe.hpp"

namespace
{
    using Board = std::vector<std::string>;

    GameBoard MakeBoard(const Board& rows)
    {
        GameBoard board{};

        for (int row = 0; row < 3; ++row)
        {
            for (int column = 0; column < 3; ++column)
            {
                board.cells[row][column] = rows[row][column];
            }
        }

        return board;
    }

    void ExpectPositionScore(
        const PositionScore& actual,
        GameResult expectedResult,
        int expectedDistance,
        int expectedNextPlayerWinCount)
    {
        EXPECT_EQ(actual.result, expectedResult);
        EXPECT_EQ(actual.distance, expectedDistance);
        EXPECT_EQ(actual.next_player_win_count, expectedNextPlayerWinCount);
    }
}

// №1
TEST(TicTacToeSolverEvaluatePositionTests, TerminalPositionIsWinForStrategyPlayerX)
{
    GameBoard board = MakeBoard({
        "XXX",
        "OO.",
        "..."
    });

    TicTacToeSolver solver{};

    PositionScore score = solver.EvaluatePosition(board, 'O', 'X');

    ExpectPositionScore(score, WIN, 0, 0);
}

// №2
TEST(TicTacToeSolverEvaluatePositionTests, TerminalPositionIsDraw)
{
    GameBoard board = MakeBoard({
        "XOX",
        "XOO",
        "OXX"
    });

    TicTacToeSolver solver{};

    PositionScore score = solver.EvaluatePosition(board, 'X', 'X');

    ExpectPositionScore(score, DRAW, 0, 0);
}

// №3
TEST(TicTacToeSolverEvaluatePositionTests, StrategyPlayerXWinsNextMove)
{
    GameBoard board = MakeBoard({
        "XX.",
        "OO.",
        "..."
    });

    TicTacToeSolver solver{};

    PositionScore score = solver.EvaluatePosition(board, 'X', 'X');

    ExpectPositionScore(score, WIN, 1, 1);
}

// №4
TEST(TicTacToeSolverEvaluatePositionTests, OpponentOfStrategyPlayerOWinsNextMove)
{
    GameBoard board = MakeBoard({
        "XX.",
        "OO.",
        "..."
    });

    TicTacToeSolver solver{};

    PositionScore score = solver.EvaluatePosition(board, 'X', 'O');

    ExpectPositionScore(score, LOSE, 1, 1);
}

// №5
TEST(TicTacToeSolverEvaluatePositionTests, OnlyRemainingMoveLeadsToDraw)
{
    GameBoard board = MakeBoard({
        "XOX",
        "XOO",
        "O.X"
    });

    TicTacToeSolver solver{};

    PositionScore score = solver.EvaluatePosition(board, 'X', 'X');

    ExpectPositionScore(score, DRAW, 1, 0);
}

// №6
TEST(TicTacToeSolverEvaluatePositionTests, OpponentMakesEquivalentMoveLeadingToDraw)
{
    GameBoard board = MakeBoard({
        "XXO",
        "OOX",
        "X.."
    });

    TicTacToeSolver solver{};

    PositionScore score = solver.EvaluatePosition(board, 'O', 'X');

    ExpectPositionScore(score, DRAW, 2, 0);
}

// №7
TEST(TicTacToeSolverEvaluatePositionTests, StrategyPlayerOHasSeveralWinningContinuations)
{
    GameBoard board = MakeBoard({
        "XXO",
        "XX.",
        "O.O"
    });

    TicTacToeSolver solver{};

    PositionScore score = solver.EvaluatePosition(board, 'O', 'O');

    ExpectPositionScore(score, WIN, 1, 1);
}

// №8
TEST(TicTacToeSolverEvaluatePositionTests, ImmediateWinXIsSelectedFromSeveralWinningContinuations)
{
    GameBoard board = MakeBoard({
        "XXO",
        "X.O",
        ".O."
    });

    TicTacToeSolver solver{};

    PositionScore score = solver.EvaluatePosition(board, 'X', 'X');

    ExpectPositionScore(score, WIN, 1, 1);
}

// №9
TEST(TicTacToeSolverEvaluatePositionTests, StrategyPlayerXChoosesLaterLossWhenLossIsInevitable)
{
    GameBoard board = MakeBoard({
        "XXO",
        "..O",
        "..."
    });

    TicTacToeSolver solver{};

    PositionScore score = solver.EvaluatePosition(board, 'X', 'X');

    ExpectPositionScore(score, LOSE, 4, 0);
}

// №10
TEST(TicTacToeSolverEvaluatePositionTests, OpponentDelaysStrategyPlayerXWin)
{
    GameBoard board = MakeBoard({
        "XX.",
        "O.X",
        "O.."
    });

    TicTacToeSolver solver{};

    PositionScore score = solver.EvaluatePosition(board, 'O', 'X');

    ExpectPositionScore(score, WIN, 4, 0);
}

// №11
TEST(TicTacToeSolverEvaluatePositionTests, OpponentOfStrategyPlayerXHoldsDraw)
{
    GameBoard board = MakeBoard({
        "XXO",
        "O.X",
        "..."
    });

    TicTacToeSolver solver{};

    PositionScore score = solver.EvaluatePosition(board, 'O', 'X');

    ExpectPositionScore(score, DRAW, 4, 0);
}

// №12
TEST(TicTacToeSolverEvaluatePositionTests, StrategyPlayerXHasOnlyLineToDraw)
{
    GameBoard board = MakeBoard({
        "XXO",
        ".O.",
        "..."
    });

    TicTacToeSolver solver{};

    PositionScore score = solver.EvaluatePosition(board, 'X', 'X');

    ExpectPositionScore(score, DRAW, 5, 0);
}

// №13
TEST(TicTacToeSolverEvaluatePositionTests, OpponentBlocksThreatAndLeadsToLongDraw)
{
    GameBoard board = MakeBoard({
        "XX.",
        ".O.",
        "..."
    });

    TicTacToeSolver solver{};

    PositionScore score = solver.EvaluatePosition(board, 'O', 'X');

    ExpectPositionScore(score, DRAW, 6, 0);
}

// №14
TEST(TicTacToeSolverEvaluatePositionTests, OpponentBlocksThreatAndLeadsToLongDrawMirrored)
{
    GameBoard board = MakeBoard({
        "...",
        ".O.",
        ".XX"
    });

    TicTacToeSolver solver{};

    PositionScore score = solver.EvaluatePosition(board, 'O', 'X');

    ExpectPositionScore(score, DRAW, 6, 0);
}

// №15
TEST(TicTacToeSolverEvaluatePositionTests, StrategyPlayerXCannotAvoidLossInTwoMoves)
{
    GameBoard board = MakeBoard({
        "XXO",
        "X.O",
        "O.."
    });

    TicTacToeSolver solver{};

    PositionScore score = solver.EvaluatePosition(board, 'X', 'X');

    ExpectPositionScore(score, LOSE, 2, 1);
}

// №16
TEST(TicTacToeSolverEvaluatePositionTests, StrategyPlayerXChoosesMoveWithFewerImmediateOpponentWins)
{
    GameBoard board = MakeBoard({
        "XXO",
        "X..",
        "O.O"
    });

    TicTacToeSolver solver{};

    PositionScore score = solver.EvaluatePosition(board, 'X', 'X');

    ExpectPositionScore(score, LOSE, 2, 2);
}