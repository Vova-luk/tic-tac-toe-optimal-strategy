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
}

// №1
TEST(TicTacToeSolverBuildOptimalTreeTests, TerminalPositionWithXWinHasNoChildren)
{
    GameBoard board = MakeBoard({
        "XXX",
        "OO.",
        "..."
    });

    TicTacToeSolver solver{};

    TreeNode* tree = solver.BuildOptimalTree(board, 'O', 'X');

    ExpectTreeNode(
        tree,
        {
            "XXX",
            "OO.",
            "..."
        },
        0u);

    
}

// №3
TEST(TicTacToeSolverBuildOptimalTreeTests, TerminalDrawPositionHasNoChildren)
{
    GameBoard board = MakeBoard({
        "XOX",
        "XOO",
        "OXX"
    });

    TicTacToeSolver solver{};

    TreeNode* tree = solver.BuildOptimalTree(board, 'X', 'X');

    ExpectTreeNode(
        tree,
        {
            "XOX",
            "XOO",
            "OXX"
        },
        0u);

    
}

// №4
TEST(TicTacToeSolverBuildOptimalTreeTests, StrategyPlayerXChoosesOnlyImmediateWin)
{
    GameBoard board = MakeBoard({
        "XX.",
        "OO.",
        "..."
    });

    TicTacToeSolver solver{};

    TreeNode* tree = solver.BuildOptimalTree(board, 'X', 'X');

    ExpectTreeNode(
        tree,
        {
            "XX.",
            "OO.",
            "..."
        },
        1u);

    ASSERT_EQ(tree->children.size(), 1u);

    ExpectTreeNode(
        tree->children[0],
        {
            "XXX",
            "OO.",
            "..."
        },
        0u);

    
}

// №5
TEST(TicTacToeSolverBuildOptimalTreeTests, StrategyPlayerOHasTwoEquivalentImmediateWins)
{
    GameBoard board = MakeBoard({
        "XXO",
        "XX.",
        "O.O"
    });

    TicTacToeSolver solver{};

    TreeNode* tree = solver.BuildOptimalTree(board, 'O', 'O');

    ExpectTreeNode(
        tree,
        {
            "XXO",
            "XX.",
            "O.O"
        },
        2u);

    const TreeNode* firstWinningChild = FindChildByBoard(
        tree,
        {
            "XXO",
            "XXO",
            "O.O"
        });

    ASSERT_NE(firstWinningChild, nullptr);
    ExpectTreeNode(
        firstWinningChild,
        {
            "XXO",
            "XXO",
            "O.O"
        },
        0u);

    const TreeNode* secondWinningChild = FindChildByBoard(
        tree,
        {
            "XXO",
            "XX.",
            "OOO"
        });

    ASSERT_NE(secondWinningChild, nullptr);
    ExpectTreeNode(
        secondWinningChild,
        {
            "XXO",
            "XX.",
            "OOO"
        },
        0u);

    
}

// №6
TEST(TicTacToeSolverBuildOptimalTreeTests, OnlyOptimalOpponentMoveLeadsToDraw)
{
    GameBoard board = MakeBoard({
        "..O",
        "OXX",
        "XOX"
    });

    TicTacToeSolver solver{};

    TreeNode* tree = solver.BuildOptimalTree(board, 'O', 'X');

    ExpectTreeNode(
        tree,
        {
            "..O",
            "OXX",
            "XOX"
        },
        1u);

    ASSERT_EQ(tree->children.size(), 1u);

    TreeNode* firstLevel = tree->children[0];

    ExpectTreeNode(
        firstLevel,
        {
            "O.O",
            "OXX",
            "XOX"
        },
        1u);

    ASSERT_EQ(firstLevel->children.size(), 1u);

    ExpectTreeNode(
        firstLevel->children[0],
        {
            "OXO",
            "OXX",
            "XOX"
        },
        0u);

    
}

// №7
TEST(TicTacToeSolverBuildOptimalTreeTests, StrategyPlayerXHasThreeEquivalentImmediateWins)
{
    GameBoard board = MakeBoard({
        "..O",
        "OXO",
        ".XX"
    });

    TicTacToeSolver solver{};

    TreeNode* tree = solver.BuildOptimalTree(board, 'X', 'X');

    ExpectTreeNode(
        tree,
        {
            "..O",
            "OXO",
            ".XX"
        },
        3u);

    const TreeNode* firstWinningChild = FindChildByBoard(
        tree,
        {
            "X.O",
            "OXO",
            ".XX"
        });

    ASSERT_NE(firstWinningChild, nullptr);
    ExpectTreeNode(
        firstWinningChild,
        {
            "X.O",
            "OXO",
            ".XX"
        },
        0u);

    const TreeNode* secondWinningChild = FindChildByBoard(
        tree,
        {
            ".XO",
            "OXO",
            ".XX"
        });

    ASSERT_NE(secondWinningChild, nullptr);
    ExpectTreeNode(
        secondWinningChild,
        {
            ".XO",
            "OXO",
            ".XX"
        },
        0u);

    const TreeNode* thirdWinningChild = FindChildByBoard(
        tree,
        {
            "..O",
            "OXO",
            "XXX"
        });

    ASSERT_NE(thirdWinningChild, nullptr);
    ExpectTreeNode(
        thirdWinningChild,
        {
            "..O",
            "OXO",
            "XXX"
        },
        0u);

    
}

// №8
TEST(TicTacToeSolverBuildOptimalTreeTests, OpponentHasTwoEquivalentMovesAfterWhichXWins)
{
    GameBoard board = MakeBoard({
        "...",
        ".XO",
        "OXX"
    });

    TicTacToeSolver solver{};

    TreeNode* tree = solver.BuildOptimalTree(board, 'O', 'X');

    ExpectTreeNode(
        tree,
        {
            "...",
            ".XO",
            "OXX"
        },
        2u);

    const TreeNode* firstOpponentMove = FindChildByBoard(
        tree,
        {
            "O..",
            ".XO",
            "OXX"
        });

    ASSERT_NE(firstOpponentMove, nullptr);
    ExpectTreeNode(
        firstOpponentMove,
        {
            "O..",
            ".XO",
            "OXX"
        },
        1u);

    ASSERT_EQ(firstOpponentMove->children.size(), 1u);

    ExpectTreeNode(
        firstOpponentMove->children[0],
        {
            "OX.",
            ".XO",
            "OXX"
        },
        0u);

    const TreeNode* secondOpponentMove = FindChildByBoard(
        tree,
        {
            ".O.",
            ".XO",
            "OXX"
        });

    ASSERT_NE(secondOpponentMove, nullptr);
    ExpectTreeNode(
        secondOpponentMove,
        {
            ".O.",
            ".XO",
            "OXX"
        },
        1u);

    ASSERT_EQ(secondOpponentMove->children.size(), 1u);

    ExpectTreeNode(
        secondOpponentMove->children[0],
        {
            "XO.",
            ".XO",
            "OXX"
        },
        0u);

    
}

// №9
TEST(TicTacToeSolverBuildOptimalTreeTests, StrategyPlayerXLosesWithTwoEquivalentOResponses)
{
    GameBoard board = MakeBoard({
        "...",
        "XOX",
        "OXO"
    });

    TicTacToeSolver solver{};

    TreeNode* tree = solver.BuildOptimalTree(board, 'X', 'X');

    ExpectTreeNode(
        tree,
        {
            "...",
            "XOX",
            "OXO"
        },
        2u);

    const TreeNode* firstXMove = FindChildByBoard(
        tree,
        {
            "X..",
            "XOX",
            "OXO"
        });

    ASSERT_NE(firstXMove, nullptr);
    ExpectTreeNode(
        firstXMove,
        {
            "X..",
            "XOX",
            "OXO"
        },
        1u);

    ASSERT_EQ(firstXMove->children.size(), 1u);

    ExpectTreeNode(
        firstXMove->children[0],
        {
            "X.O",
            "XOX",
            "OXO"
        },
        0u);

    const TreeNode* secondXMove = FindChildByBoard(
        tree,
        {
            "..X",
            "XOX",
            "OXO"
        });

    ASSERT_NE(secondXMove, nullptr);
    ExpectTreeNode(
        secondXMove,
        {
            "..X",
            "XOX",
            "OXO"
        },
        1u);

    ASSERT_EQ(secondXMove->children.size(), 1u);

    ExpectTreeNode(
        secondXMove->children[0],
        {
            "O.X",
            "XOX",
            "OXO"
        },
        0u);

    
}

// №10
TEST(TicTacToeSolverBuildOptimalTreeTests, OnlyOptimalBranchLeadsToDrawInThreeMoves)
{
    GameBoard board = MakeBoard({
        "..O",
        ".OX",
        "XXO"
    });

    TicTacToeSolver solver{};

    TreeNode* tree = solver.BuildOptimalTree(board, 'X', 'X');

    ExpectTreeNode(
        tree,
        {
            "..O",
            ".OX",
            "XXO"
        },
        1u);

    ASSERT_EQ(tree->children.size(), 1u);

    TreeNode* firstLevel = tree->children[0];

    ExpectTreeNode(
        firstLevel,
        {
            "X.O",
            ".OX",
            "XXO"
        },
        1u);

    ASSERT_EQ(firstLevel->children.size(), 1u);

    TreeNode* secondLevel = firstLevel->children[0];

    ExpectTreeNode(
        secondLevel,
        {
            "X.O",
            "OOX",
            "XXO"
        },
        1u);

    ASSERT_EQ(secondLevel->children.size(), 1u);

    ExpectTreeNode(
        secondLevel->children[0],
        {
            "XXO",
            "OOX",
            "XXO"
        },
        0u);

    
}

// №11
TEST(TicTacToeSolverBuildOptimalTreeTests, DrawPositionHasTwoOptimalBranchesOnSecondLevel)
{
    GameBoard board = MakeBoard({
        "...",
        "OOX",
        "XXO"
    });

    TicTacToeSolver solver{};

    TreeNode* tree = solver.BuildOptimalTree(board, 'X', 'X');

    ExpectTreeNode(
        tree,
        {
            "...",
            "OOX",
            "XXO"
        },
        1u);

    ASSERT_EQ(tree->children.size(), 1u);

    TreeNode* firstLevel = tree->children[0];

    ExpectTreeNode(
        firstLevel,
        {
            "X..",
            "OOX",
            "XXO"
        },
        2u);

    const TreeNode* firstSecondLevelBranch = FindChildByBoard(
        firstLevel,
        {
            "XO.",
            "OOX",
            "XXO"
        });

    ASSERT_NE(firstSecondLevelBranch, nullptr);
    ExpectTreeNode(
        firstSecondLevelBranch,
        {
            "XO.",
            "OOX",
            "XXO"
        },
        1u);

    ASSERT_EQ(firstSecondLevelBranch->children.size(), 1u);

    ExpectTreeNode(
        firstSecondLevelBranch->children[0],
        {
            "XOX",
            "OOX",
            "XXO"
        },
        0u);

    const TreeNode* secondSecondLevelBranch = FindChildByBoard(
        firstLevel,
        {
            "X.O",
            "OOX",
            "XXO"
        });

    ASSERT_NE(secondSecondLevelBranch, nullptr);
    ExpectTreeNode(
        secondSecondLevelBranch,
        {
            "X.O",
            "OOX",
            "XXO"
        },
        1u);

    ASSERT_EQ(secondSecondLevelBranch->children.size(), 1u);

    ExpectTreeNode(
        secondSecondLevelBranch->children[0],
        {
            "XXO",
            "OOX",
            "XXO"
        },
        0u);

    
}

// №12
TEST(TicTacToeSolverBuildOptimalTreeTests, OpponentBuildsStrategyPlayerXLossInThreeMoves)
{
    GameBoard board = MakeBoard({
        "...",
        "X.X",
        "OXO"
    });

    TicTacToeSolver solver{};

    TreeNode* tree = solver.BuildOptimalTree(board, 'O', 'X');

    ExpectTreeNode(
        tree,
        {
            "...",
            "X.X",
            "OXO"
        },
        1u);

    ASSERT_EQ(tree->children.size(), 1u);

    TreeNode* firstLevel = tree->children[0];

    ExpectTreeNode(
        firstLevel,
        {
            "...",
            "XOX",
            "OXO"
        },
        2u);

    const TreeNode* firstSecondLevelBranch = FindChildByBoard(
        firstLevel,
        {
            "X..",
            "XOX",
            "OXO"
        });

    ASSERT_NE(firstSecondLevelBranch, nullptr);
    ExpectTreeNode(
        firstSecondLevelBranch,
        {
            "X..",
            "XOX",
            "OXO"
        },
        1u);

    ASSERT_EQ(firstSecondLevelBranch->children.size(), 1u);

    ExpectTreeNode(
        firstSecondLevelBranch->children[0],
        {
            "X.O",
            "XOX",
            "OXO"
        },
        0u);

    const TreeNode* secondSecondLevelBranch = FindChildByBoard(
        firstLevel,
        {
            "..X",
            "XOX",
            "OXO"
        });

    ASSERT_NE(secondSecondLevelBranch, nullptr);
    ExpectTreeNode(
        secondSecondLevelBranch,
        {
            "..X",
            "XOX",
            "OXO"
        },
        1u);

    ASSERT_EQ(secondSecondLevelBranch->children.size(), 1u);

    ExpectTreeNode(
        secondSecondLevelBranch->children[0],
        {
            "O.X",
            "XOX",
            "OXO"
        },
        0u);

    
}

// №15
TEST(TicTacToeSolverBuildOptimalTreeTests, OpponentOHasSeveralOptimalBranchesToWin)
{
    GameBoard board = MakeBoard({
        ".O.",
        "XOX",
        ".X."
    });

    TicTacToeSolver solver{};

    TreeNode* tree = solver.BuildOptimalTree(board, 'O', 'X');

    ExpectTreeNode(
        tree,
        {
            ".O.",
            "XOX",
            ".X."
        },
        2u);

    const TreeNode* firstOpponentBranch = FindChildByBoard(
        tree,
        {
            "OO.",
            "XOX",
            ".X."
        });

    ASSERT_NE(firstOpponentBranch, nullptr);
    ExpectTreeNode(
        firstOpponentBranch,
        {
            "OO.",
            "XOX",
            ".X."
        },
        2u);

    const TreeNode* firstBranchFirstXMove = FindChildByBoard(
        firstOpponentBranch,
        {
            "OOX",
            "XOX",
            ".X."
        });

    ASSERT_NE(firstBranchFirstXMove, nullptr);
    ExpectTreeNode(
        firstBranchFirstXMove,
        {
            "OOX",
            "XOX",
            ".X."
        },
        1u);

    ASSERT_EQ(firstBranchFirstXMove->children.size(), 1u);

    ExpectTreeNode(
        firstBranchFirstXMove->children[0],
        {
            "OOX",
            "XOX",
            ".XO"
        },
        0u);

    const TreeNode* firstBranchSecondXMove = FindChildByBoard(
        firstOpponentBranch,
        {
            "OO.",
            "XOX",
            ".XX"
        });

    ASSERT_NE(firstBranchSecondXMove, nullptr);
    ExpectTreeNode(
        firstBranchSecondXMove,
        {
            "OO.",
            "XOX",
            ".XX"
        },
        1u);

    ASSERT_EQ(firstBranchSecondXMove->children.size(), 1u);

    ExpectTreeNode(
        firstBranchSecondXMove->children[0],
        {
            "OOO",
            "XOX",
            ".XX"
        },
        0u);

    const TreeNode* secondOpponentBranch = FindChildByBoard(
        tree,
        {
            ".OO",
            "XOX",
            ".X."
        });

    ASSERT_NE(secondOpponentBranch, nullptr);
    ExpectTreeNode(
        secondOpponentBranch,
        {
            ".OO",
            "XOX",
            ".X."
        },
        2u);

    const TreeNode* secondBranchFirstXMove = FindChildByBoard(
        secondOpponentBranch,
        {
            "XOO",
            "XOX",
            ".X."
        });

    ASSERT_NE(secondBranchFirstXMove, nullptr);
    ExpectTreeNode(
        secondBranchFirstXMove,
        {
            "XOO",
            "XOX",
            ".X."
        },
        1u);

    ASSERT_EQ(secondBranchFirstXMove->children.size(), 1u);

    ExpectTreeNode(
        secondBranchFirstXMove->children[0],
        {
            "XOO",
            "XOX",
            "OX."
        },
        0u);

    const TreeNode* secondBranchSecondXMove = FindChildByBoard(
        secondOpponentBranch,
        {
            ".OO",
            "XOX",
            "XX."
        });

    ASSERT_NE(secondBranchSecondXMove, nullptr);
    ExpectTreeNode(
        secondBranchSecondXMove,
        {
            ".OO",
            "XOX",
            "XX."
        },
        1u);

    ASSERT_EQ(secondBranchSecondXMove->children.size(), 1u);

    ExpectTreeNode(
        secondBranchSecondXMove->children[0],
        {
            "OOO",
            "XOX",
            "XX."
        },
        0u);

    
}