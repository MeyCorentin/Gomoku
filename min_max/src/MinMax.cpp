#include "../includes/MinMax.hpp"

MinMax::MinMax()
{

}

MinMax::~MinMax()
{

}

node MinMax::findBestMove(int depth, int nodeIndex, bool isMax, std::vector<node> scores, int maxDepth)
{
    if (depth == maxDepth)
        return scores.at(nodeIndex);

    if (isMax) {
        node node_left = findBestMove(depth + 1, nodeIndex * 2, false, scores, maxDepth);
        node node_right = findBestMove(depth + 1, nodeIndex * 2 + 1, false, scores, maxDepth);
        if (node_left.score > node_right.score)
            return node_left;
        else
            return node_right;
    } else {
        node node_left = findBestMove(depth + 1, nodeIndex * 2, true, scores, maxDepth);
        node node_right = findBestMove(depth + 1, nodeIndex * 2 + 1, true, scores, maxDepth);
        if (node_left.score > node_right.score)
            return node_right;
        else
            return node_left;
    }
}

int MinMax::getMaxDepth(int size)
{
    return (size == 1) ? 0 : 1 + getMaxDepth(size / 2);
}