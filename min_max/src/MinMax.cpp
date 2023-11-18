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
    
    node result_{1,1,1};
    for(auto temp: _scores)
    {
        if (temp.score > result_.score)
        {
            result_.score = temp.score;
            result_.i = temp.i;
            result_.i_vector = temp.i_vector;
        }
    }
    std::cout << result_.score << std::endl;
    return result_;
}

int MinMax::getMaxDepth(int size)
{
    return (size == 1) ? 0 : 1 + getMaxDepth(size / 2);
}

double MinMax::recurseScore(double score_, int depth, double alpha, double beta, std::pair<int, int> position, std::pair<int, int> direction)
{
    if (depth == 0)
        return score_;

    if (position.first >( _bitboard->getRowSize() / 2) || position.second >( _bitboard->getRowSize() / 2) || position.first < 1 || position.second < 1)
        return score_;

    position.first += direction.first;
    position.second += direction.second;

    double child_score = recurseScore(score_, depth--, alpha, beta, position, direction) / 2;

    score_ = (score_ + child_score) / 2;

    int color  = _bitboard->getBitboardColor(_bitboard->getIndex(position));
    if (color== 1)
        score_ += 10;
    if (color== 2)
        score_ += 5;

    return score_ * 0.9;
}

double MinMax::updateScore(int index)
{
    double score = 0;
    int depth = 1;
    std::pair<int, int> position = _bitboard->getPosition(index);
    if (_bitboard->getBitboardColor(_bitboard->getIndex(position)) != 0)
        return -1;
    score = recurseScore(score, depth--, -INFINITY, INFINITY, position, std::make_pair(-1,0)); //Leftx
    score = recurseScore(score, depth--, -INFINITY, INFINITY, position, std::make_pair(0,-1)); //Top
    score = recurseScore(score, depth--, -INFINITY, INFINITY, position, std::make_pair(1,0)); //Right
    score = recurseScore(score, depth--, -INFINITY, INFINITY, position, std::make_pair(0,1)); //Bottom
    score = recurseScore(score, depth--, -INFINITY, INFINITY, position, std::make_pair(-1,-1)); //Top Left
    score = recurseScore(score, depth--, -INFINITY, INFINITY, position, std::make_pair(1,-1)); //Top Right
    score = recurseScore(score, depth--, -INFINITY, INFINITY, position, std::make_pair(1,1)); //Bottom Right
    score = recurseScore(score, depth--, -INFINITY, INFINITY, position, std::make_pair(-1,1)); //Bottom Left
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