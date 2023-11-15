#include "../includes/MinMax.hpp"

MinMax::MinMax(Bitboard *bitboard)
{
    _bitboard = bitboard;
    _scores = {};
}

MinMax::~MinMax()
{

}

node MinMax::findBestMove(int depth, int nodeIndex, bool isMax, int maxDepth)
{
    if (depth == maxDepth)
        return _scores.at(nodeIndex);

    if (isMax) {
        node node_left = findBestMove(depth + 1, nodeIndex * 2, false, maxDepth);
        node node_right = findBestMove(depth + 1, nodeIndex * 2 + 1, false, maxDepth);
        if (node_left.score > node_right.score)
            return node_left;
        else
            return node_right;
    } else {
        node node_left = findBestMove(depth + 1, nodeIndex * 2, true, maxDepth);
        node node_right = findBestMove(depth + 1, nodeIndex * 2 + 1, true, maxDepth);
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

int MinMax::updateScore(int case_score, int temp_size_, int i)
{
    // if (openEnds == 0 && countConsecutive < 5)
        

}


void MinMax::getScoreInMap()
{
    std::vector<uint64_t> board_ = _bitboard->getBitboard();
    int temp_size_ = 0;
    int board_count_ = 0;
    int case_score = 0;
    int i;

    for (; temp_size_ < _bitboard->getSize();) {
        for (int i = 1; i <= 64; i+=2) {
            temp_size_++;
            if (temp_size_ >= _bitboard->getSize())
                break;
            if (temp_size_ % _bitboard->getRowSize() == 0)
                std::cout << std::endl;
            uint64_t mask_2 = 1ULL << (i + 1);
            if (board_[board_count_] & mask_2)
            {
                uint64_t mask = 1ULL << i;
                if (board_[board_count_] & mask) {
                    std::cout << temp_size_  + _bitboard->getRowSize() << std::endl;
                    std::cout << _bitboard->getPosition(temp_size_ + _bitboard->getRowSize()).first  << std::endl;
                    std::cout << _bitboard->getPosition(temp_size_ + _bitboard->getRowSize()).second  << std::endl;
                    std::cout << _bitboard->getIndex(_bitboard->getPosition(temp_size_ + _bitboard->getRowSize())) << std::endl;;
                }
            }
        }
        board_count_++;
    }
    std::cout << std::endl;
}

std::pair<int, int> MinMax::nodeToPosition(node my_node)
{
    std::pair<int, int> result;

    result.first = my_node.i_vector; //TODO Change that
    result.second = my_node.i; //TODO Change that
    return result;
}

std::pair<int, int> MinMax::playTurn()
{
    getScoreInMap();
    // int size = _scores.size();
    // int maxDepth = getMaxDepth(size);

    // node result = findBestMove(0, 0, true, maxDepth);
    // std::pair<int, int> position = nodeToPosition(result);

    // std::cout << "Result : " << result.score << std::endl;

    // std::cout << "SUGGEST [" << position.first << "] [" << position.second << "]" << std::endl;
    return std::make_pair(0,0);
}