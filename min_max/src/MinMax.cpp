#include "../includes/MinMax.hpp"

MinMax::MinMax()
{

}

MinMax::~MinMax()
{

}

int MinMax::findBestMove(int depth, int nodeIndex, bool isMax, int scores[], int maxDepth)
{
    if (depth == maxDepth)
        return scores[nodeIndex];

    if (isMax) {
        return std::max(findBestMove(depth + 1, nodeIndex * 2, false, scores, maxDepth), findBestMove(depth + 1, nodeIndex * 2 + 1, false, scores, maxDepth));
    } else {
        return std::min(findBestMove(depth + 1, nodeIndex * 2, true, scores, maxDepth), findBestMove(depth + 1, nodeIndex * 2 + 1, true, scores, maxDepth));
    }
}

int MinMax::getMaxDepth(int size)
{
    return (size == 1) ? 0 : 1 + getMaxDepth(size / 2);
}