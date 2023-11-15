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

int MinMax::recurseScore(int score, std::pair<int, int> position, std::pair<int, int> direction)
{
    if (position.first >= _bitboard->getSize() || position.second >= _bitboard->getSize() || position.first < 0 || position.second < 0)
        return score;

    position.first += direction.first;
    position.second += direction.second;
    score += recurseScore(score, position, direction);

    if (_bitboard->getBitboardColor(_bitboard->getIndex(position)) == 1)
        score += 1;

    return score;
}

int MinMax::updateScore(int index) //Todo change direction by value
{
    int score = 0;
    std::pair<int, int> position = _bitboard->getPosition(index);

    score += recurseScore(0, position, std::make_pair(-1,0)); //Left
    score += recurseScore(0, position, std::make_pair(-1,-1)); //Top Left
    score += recurseScore(0, position, std::make_pair(0,-1)); //Top
    score += recurseScore(0, position, std::make_pair(1,-1)); //Top Right
    score += recurseScore(0, position, std::make_pair(1,0)); //Right
    score += recurseScore(0, position, std::make_pair(1,1)); //Bottom Right
    score += recurseScore(0, position, std::make_pair(0,1)); //Bottom
    score += recurseScore(0, position, std::make_pair(-1,1)); //Bottom Left
    std::cout << "|" << score << "|";
    return score;
}


void MinMax::getScoreInMap()
{
    std::vector<uint64_t> board_ = _bitboard->getBitboard();
    int temp_size_ = -1;
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
            // _bitboard->getBitboardColor(temp_size_  + _bitboard->getRowSize());
            _scores.push_back(node{updateScore(temp_size_  + _bitboard->getRowSize()), (int)_scores.size() + 1,temp_size_  + _bitboard->getRowSize()});
        }
        board_count_++;
    }
}

std::pair<int, int> MinMax::nodeToPosition(node my_node)
{
    return _bitboard->getPosition(my_node.i_vector);
}

std::pair<int, int> MinMax::playTurn()
{
    getScoreInMap();
    int size = _scores.size();
    int maxDepth = getMaxDepth(size);

    node result = findBestMove(0, 0, true, maxDepth);
    std::pair<int, int> position = nodeToPosition(result);

    std::cout << "Result : " << result.score << std::endl;

    std::cout << "SUGGEST [" << position.first << "] [" << position.second << "]" << std::endl;
    return std::make_pair(position.first, position.second);
}