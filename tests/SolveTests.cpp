#include <gtest/gtest.h>

#include <cstddef>
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

    StrategyTask MakeTask(
        const Board& board,
        char strategyPlayer,
        char nextPlayer)
    {
        StrategyTask task{};
        task.board = MakeBoard(board);
        task.strategy_player = strategyPlayer;
        task.next_player = nextPlayer;
        return task;
    }

    bool IsBoardEq(const GameBoard& actual, const Board& expected)
    {
        if (expected.size() != 3u)
        {
            return false;
        }

        for (int row = 0; row < 3; ++row)
        {
            if (expected[row].size() != 3u)
            {
                return false;
            }

            for (int column = 0; column < 3; ++column)
            {
                if (actual.cells[row][column] != expected[row][column])
                {
                    return false;
                }
            }
        }

        return true;
    }

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

    void ExpectTreeNode(
        const TreeNode* node,
        const Board& expectedBoard,
        std::size_t expectedChildrenCount)
    {
        ASSERT_NE(node, nullptr);
        ExpectBoardEq(node->board, expectedBoard);
        EXPECT_EQ(node->children.size(), expectedChildrenCount);
    }

    const TreeNode* FindChildByBoard(
        const TreeNode* node,
        const Board& expectedBoard)
    {
        if (node == nullptr)
        {
            return nullptr;
        }

        for (const TreeNode* child : node->children)
        {
            if (child != nullptr && IsBoardEq(child->board, expectedBoard))
            {
                return child;
            }
        }

        return nullptr;
    }

    void ExpectChildExists(
        const TreeNode* node,
        const Board& expectedBoard,
        std::size_t expectedChildrenCount)
    {
        const TreeNode* child = FindChildByBoard(node, expectedBoard);

        ASSERT_NE(child, nullptr);
        ExpectTreeNode(child, expectedBoard, expectedChildrenCount);
    }

    std::size_t CountTreeNodes(const TreeNode* node)
    {
        if (node == nullptr)
        {
            return 0;
        }

        std::size_t count = 1;

        for (const TreeNode* child : node->children)
        {
            count += CountTreeNodes(child);
        }

        return count;
    }
}

// №1
TEST(TicTacToeSolverSolveTests, TerminalPositionWithStrategyPlayerXWin)
{
    StrategyTask task = MakeTask(
        {
            "XXX",
            "OO.",
            "..."
        },
        'X',
        'O');

    TicTacToeSolver solver{};
    TreeNode* resultTree = nullptr;

    GameResult result = solver.Solve(task, resultTree);

    EXPECT_EQ(result, WIN);
    ExpectTreeNode(
        resultTree,
        {
            "XXX",
            "OO.",
            "..."
        },
        0u);

    
}

// №2
TEST(TicTacToeSolverSolveTests, TerminalPositionWithStrategyPlayerOLose)
{
    StrategyTask task = MakeTask(
        {
            "XXX",
            "OO.",
            "..."
        },
        'O',
        'O');

    TicTacToeSolver solver{};
    TreeNode* resultTree = nullptr;

    GameResult result = solver.Solve(task, resultTree);

    EXPECT_EQ(result, LOSE);
    ExpectTreeNode(
        resultTree,
        {
            "XXX",
            "OO.",
            "..."
        },
        0u);
}

// №3
TEST(TicTacToeSolverSolveTests, TerminalDrawPosition)
{
    StrategyTask task = MakeTask(
        {
            "XOX",
            "XOO",
            "OXX"
        },
        'X',
        'O');

    TicTacToeSolver solver{};
    TreeNode* resultTree = nullptr;

    GameResult result = solver.Solve(task, resultTree);

    EXPECT_EQ(result, DRAW);
    ExpectTreeNode(
        resultTree,
        {
            "XOX",
            "XOO",
            "OXX"
        },
        0u);
}

// №4
TEST(TicTacToeSolverSolveTests, StrategyPlayerXWinsNextMove)
{
    StrategyTask task = MakeTask(
        {
            "XX.",
            "OO.",
            "..."
        },
        'X',
        'X');

    TicTacToeSolver solver{};
    TreeNode* resultTree = nullptr;

    GameResult result = solver.Solve(task, resultTree);

    EXPECT_EQ(result, WIN);

    ExpectTreeNode(
        resultTree,
        {
            "XX.",
            "OO.",
            "..."
        },
        1u);

    ExpectTreeNode(
        resultTree->children[0],
        {
            "XXX",
            "OO.",
            "..."
        },
        0u);

    
}

// №5
TEST(TicTacToeSolverSolveTests, StrategyPlayerOLosesAgainstOptimalOpponentMove)
{
    StrategyTask task = MakeTask(
        {
            "XX.",
            "OO.",
            "..."
        },
        'O',
        'X');

    TicTacToeSolver solver{};
    TreeNode* resultTree = nullptr;

    GameResult result = solver.Solve(task, resultTree);

    EXPECT_EQ(result, LOSE);

    ExpectTreeNode(
        resultTree,
        {
            "XX.",
            "OO.",
            "..."
        },
        1u);

    ExpectTreeNode(
        resultTree->children[0],
        {
            "XXX",
            "OO.",
            "..."
        },
        0u);

    
}

// №6
TEST(TicTacToeSolverSolveTests, NonTerminalPositionDrawsByLastMove)
{
    StrategyTask task = MakeTask(
        {
            "XOX",
            "XOO",
            "O.X"
        },
        'X',
        'X');

    TicTacToeSolver solver{};
    TreeNode* resultTree = nullptr;

    GameResult result = solver.Solve(task, resultTree);

    EXPECT_EQ(result, DRAW);

    ExpectTreeNode(
        resultTree,
        {
            "XOX",
            "XOO",
            "O.X"
        },
        1u);

    ExpectTreeNode(
        resultTree->children[0],
        {
            "XOX",
            "XOO",
            "OXX"
        },
        0u);

    
}

// №7
TEST(TicTacToeSolverSolveTests, TreeIncludesSeveralEquivalentOptimalMovesForDraw)
{
    StrategyTask task = MakeTask(
        {
            "XXO",
            "OOX",
            "X.."
        },
        'X',
        'O');

    TicTacToeSolver solver{};
    TreeNode* resultTree = nullptr;

    GameResult result = solver.Solve(task, resultTree);

    EXPECT_EQ(result, DRAW);

    ExpectTreeNode(
        resultTree,
        {
            "XXO",
            "OOX",
            "X.."
        },
        2u);

    ExpectChildExists(
        resultTree,
        {
            "XXO",
            "OOX",
            "XO."
        },
        1u);

    ExpectChildExists(
        resultTree,
        {
            "XXO",
            "OOX",
            "X.O"
        },
        1u);
}

// №8
TEST(TicTacToeSolverSolveTests, TreeIncludesSeveralEquivalentWinningMoves)
{
    StrategyTask task = MakeTask(
        {
            "XXO",
            "XX.",
            "O.O"
        },
        'O',
        'O');

    TicTacToeSolver solver{};
    TreeNode* resultTree = nullptr;

    GameResult result = solver.Solve(task, resultTree);

    EXPECT_EQ(result, WIN);

    ExpectTreeNode(
        resultTree,
        {
            "XXO",
            "XX.",
            "O.O"
        },
        2u);

    ExpectChildExists(
        resultTree,
        {
            "XXO",
            "XXO",
            "O.O"
        },
        0u);

    ExpectChildExists(
        resultTree,
        {
            "XXO",
            "XX.",
            "OOO"
        },
        0u);

    
}

// №9
TEST(TicTacToeSolverSolveTests, FastestWinningMoveIsSelected)
{
    StrategyTask task = MakeTask(
        {
            "XXO",
            "X.O",
            ".O."
        },
        'X',
        'X');

    TicTacToeSolver solver{};
    TreeNode* resultTree = nullptr;

    GameResult result = solver.Solve(task, resultTree);

    EXPECT_EQ(result, WIN);

    ExpectTreeNode(
        resultTree,
        {
            "XXO",
            "X.O",
            ".O."
        },
        1u);

    ExpectTreeNode(
        resultTree->children[0],
        {
            "XXO",
            "X.O",
            "XO."
        },
        0u);

    
}

// №10
TEST(TicTacToeSolverSolveTests, BuildsOptimalTreeWithThirdLevel)
{
    StrategyTask task = MakeTask(
        {
            "XXO",
            "OOX",
            "..."
        },
        'X',
        'X');

    TicTacToeSolver solver{};
    TreeNode* resultTree = nullptr;

    GameResult result = solver.Solve(task, resultTree);

    EXPECT_EQ(result, DRAW);

    ExpectTreeNode(
        resultTree,
        {
            "XXO",
            "OOX",
            "..."
        },
        1u);

    TreeNode* firstLevel = resultTree->children[0];

    ExpectTreeNode(
        firstLevel,
        {
            "XXO",
            "OOX",
            "X.."
        },
        2u);

    const TreeNode* secondLevelFirst = FindChildByBoard(
        firstLevel,
        {
            "XXO",
            "OOX",
            "XO."
        });

    ASSERT_NE(secondLevelFirst, nullptr);
    ExpectTreeNode(
        secondLevelFirst,
        {
            "XXO",
            "OOX",
            "XO."
        },
        1u);

    ExpectTreeNode(
        secondLevelFirst->children[0],
        {
            "XXO",
            "OOX",
            "XOX"
        },
        0u);

    const TreeNode* secondLevelSecond = FindChildByBoard(
        firstLevel,
        {
            "XXO",
            "OOX",
            "X.O"
        });

    ASSERT_NE(secondLevelSecond, nullptr);
    ExpectTreeNode(
        secondLevelSecond,
        {
            "XXO",
            "OOX",
            "X.O"
        },
        1u);

    ExpectTreeNode(
        secondLevelSecond->children[0],
        {
            "XXO",
            "OOX",
            "XXO"
        },
        0u);

    
}

// №11
TEST(TicTacToeSolverSolveTests, BuildsLargeOptimalTreeFromEmptyBoard)
{
    StrategyTask task = MakeTask(
        {
            "...",
            "...",
            "..."
        },
        'X',
        'X');

    TicTacToeSolver solver{};
    TreeNode* resultTree = nullptr;

    GameResult result = solver.Solve(task, resultTree);

    EXPECT_EQ(result, DRAW);

    ExpectBoardEq(
        resultTree->board,
        {
            "...",
            "...",
            "..."
        });

    EXPECT_EQ(CountTreeNodes(resultTree), 12134u);

    
}