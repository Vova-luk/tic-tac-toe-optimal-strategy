#include <vector>
#include "./tic_tac_toe.hpp"

bool ParseStrategyTask(
    const std::vector<std::string>& lines,
    StrategyTask& task,
    Error& error
) {
    return true;
}

GameResult TicTacToeSolver::Solve(const StrategyTask& task, TreeNode*& result_tree) { 
    return GameResult{};
}

PositionScore TicTacToeSolver::EvaluatePosition(
        const GameBoard& board,
        char current_player,
        char strategy_player
    ) {
        return PositionScore{};
    }

PositionScore TicTacToeSolver::EvaluateMove(
        const GameBoard& board,
        int position,
        char current_player,
        char strategy_player
    ) {
        return PositionScore{};
    }

TreeNode* TicTacToeSolver::BuildOptimalTree(
        const GameBoard& board,
        char current_player,
        char strategy_player
    ) {
    TreeNode* node = new TreeNode();

    return node;
    }