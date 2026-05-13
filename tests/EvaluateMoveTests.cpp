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
TEST(TicTacToeSolverEvaluateMoveTests, MoveXCompletesDiagonalWinForStrategyPlayer)
{
    GameBoard board = MakeBoard({
        "X.O",
        ".X.",
        "O.."
    });

    TicTacToeSolver solver{};

    PositionScore score = solver.EvaluateMove(board, 8, 'X', 'X');

    ExpectPositionScore(score, WIN, 1, 0);
}

// №2
TEST(TicTacToeSolverEvaluateMoveTests, MoveXDoesNotWinImmediatelyButKeepsForcedWin)
{
    GameBoard board = MakeBoard({
        "X.O",
        ".X.",
        "O.."
    });

    TicTacToeSolver solver{};

    PositionScore score = solver.EvaluateMove(board, 1, 'X', 'X');

    ExpectPositionScore(score, WIN, 3, 0);
}

// №3
TEST(TicTacToeSolverEvaluateMoveTests, MoveXTurnsWinningContinuationIntoDraw)
{
    GameBoard board = MakeBoard({
        "XO.",
        "OX.",
        "..."
    });

    TicTacToeSolver solver{};

    PositionScore score = solver.EvaluateMove(board, 5, 'X', 'X');

    ExpectPositionScore(score, DRAW, 5, 0);
}

// №4
TEST(TicTacToeSolverEvaluateMoveTests, MoveXCompletesImmediateDiagonalWin)
{
    GameBoard board = MakeBoard({
        "XO.",
        "OX.",
        "..."
    });

    TicTacToeSolver solver{};

    PositionScore score = solver.EvaluateMove(board, 8, 'X', 'X');

    ExpectPositionScore(score, WIN, 1, 0);
}

// №5
TEST(TicTacToeSolverEvaluateMoveTests, MoveXBlocksOThreatAndLeadsToDraw)
{
    GameBoard board = MakeBoard({
        "XX.",
        "OO.",
        "..."
    });

    TicTacToeSolver solver{};

    PositionScore score = solver.EvaluateMove(board, 5, 'X', 'X');

    ExpectPositionScore(score, DRAW, 5, 0);
}

// №6
TEST(TicTacToeSolverEvaluateMoveTests, MoveXDoesNotBlockOThreatAndLeadsToLoss)
{
    GameBoard board = MakeBoard({
        "XX.",
        "OO.",
        "..."
    });

    TicTacToeSolver solver{};

    PositionScore score = solver.EvaluateMove(board, 6, 'X', 'X');

    ExpectPositionScore(score, LOSE, 2, 1);
}

// №7
TEST(TicTacToeSolverEvaluateMoveTests, MoveXDelaysLossWhenLossIsInevitable)
{
    GameBoard board = MakeBoard({
        "XXO",
        "..O",
        "..."
    });

    TicTacToeSolver solver{};

    PositionScore score = solver.EvaluateMove(board, 8, 'X', 'X');

    ExpectPositionScore(score, LOSE, 4, 0);
}

// №8
TEST(TicTacToeSolverEvaluateMoveTests, MoveXCreatesPositionWhereOHasImmediateWin)
{
    GameBoard board = MakeBoard({
        "XXO",
        "..O",
        "..."
    });

    TicTacToeSolver solver{};

    PositionScore score = solver.EvaluateMove(board, 3, 'X', 'X');

    ExpectPositionScore(score, LOSE, 2, 1);
}

// №9
TEST(TicTacToeSolverEvaluateMoveTests, MoveODoesNotSaveFromForcedWinOfStrategyPlayerX)
{
    GameBoard board = MakeBoard({
        "XX.",
        "O.X",
        "O.."
    });

    TicTacToeSolver solver{};

    PositionScore score = solver.EvaluateMove(board, 2, 'O', 'X');

    ExpectPositionScore(score, WIN, 4, 0);
}

// №10
TEST(TicTacToeSolverEvaluateMoveTests, MoveOAllowsStrategyPlayerXToWinFaster)
{
    GameBoard board = MakeBoard({
        "XX.",
        "O.X",
        "O.."
    });

    TicTacToeSolver solver{};

    PositionScore score = solver.EvaluateMove(board, 4, 'O', 'X');

    ExpectPositionScore(score, WIN, 2, 1);
}

// №11
TEST(TicTacToeSolverEvaluateMoveTests, MoveOHoldsDrawAgainstStrategyPlayerX)
{
    GameBoard board = MakeBoard({
        "XXO",
        "O.X",
        "..."
    });

    TicTacToeSolver solver{};

    PositionScore score = solver.EvaluateMove(board, 4, 'O', 'X');

    ExpectPositionScore(score, DRAW, 4, 0);
}

// №12
TEST(TicTacToeSolverEvaluateMoveTests, MoveOAllowsXToForceWin)
{
    GameBoard board = MakeBoard({
        "XXO",
        "O.X",
        "..."
    });

    TicTacToeSolver solver{};

    PositionScore score = solver.EvaluateMove(board, 6, 'O', 'X');

    ExpectPositionScore(score, WIN, 4, 0);
}

// №13
TEST(TicTacToeSolverEvaluateMoveTests, MoveXIsForcedMoveToKeepDraw)
{
    GameBoard board = MakeBoard({
        "XXO",
        ".O.",
        "..."
    });

    TicTacToeSolver solver{};

    PositionScore score = solver.EvaluateMove(board, 6, 'X', 'X');

    ExpectPositionScore(score, DRAW, 5, 0);
}

// №14
TEST(TicTacToeSolverEvaluateMoveTests, MoveXDoesNotCloseDangerousOContinuationAndLeadsToLoss)
{
    GameBoard board = MakeBoard({
        "XXO",
        ".O.",
        "..."
    });

    TicTacToeSolver solver{};

    PositionScore score = solver.EvaluateMove(board, 3, 'X', 'X');

    ExpectPositionScore(score, LOSE, 2, 1);
}

// №15
TEST(TicTacToeSolverEvaluateMoveTests, MoveXLeavesOpponentTwoImmediateWinningPossibilities)
{
    GameBoard board = MakeBoard({
        "XXO",
        "X.O",
        "O.."
    });

    TicTacToeSolver solver{};

    PositionScore score = solver.EvaluateMove(board, 7, 'X', 'X');

    ExpectPositionScore(score, LOSE, 2, 2);
}