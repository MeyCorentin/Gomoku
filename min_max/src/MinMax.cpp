#include "../includes/MinMax.hpp"

MinMax::MinMax(Bitboard *bitboard)
{
    _bitboard = bitboard;
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

std::vector<node> MinMax::getScoreInMap()
{
    std::vector<node> scores;

    return scores;
}

std::pair<int, int> MinMax::nodeToPosition(node my_node)
{
    std::pair<int, int> result;

    result.first = my_node.i_vector; //TODO Change that
    result.second = my_node.i; //TODO Change that
    return result;
}

void MinMax::playTurn() 
{
    std::vector<node> scores = {{3, 0, 1}, {5, 0, 2}, {2, 0, 3}, {9, 0, 4}, {12, 0, 5}, {5, 0, 6}, {23, 0, 7}, {23, 0, 8}};
    // std::vector<node> scores = getScoreInMap();
    int size = scores.size();
    int maxDepth = getMaxDepth(size);

    node result = findBestMove(0, 0, true, scores, maxDepth);
    std::pair<int, int> position = nodeToPosition(result);

    std::cout << "Result : " << result.score << std::endl;

    std::cout << "SUGGEST [" << position.first << "] [" << position.second << "]" << std::endl;
}