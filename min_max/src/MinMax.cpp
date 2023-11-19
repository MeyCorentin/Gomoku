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
    node result_{1,1,std::make_pair(1, 1)};
    for(auto temp: _scores)
    {
        if (temp.score > result_.score)
        {
            result_.score = temp.score;
            result_.i = temp.i;
            result_.position = temp.position;
        }
    }
    // std::cout << result_.score << std::endl;
    return result_;
}

int MinMax::getMaxDepth(int size)
{
    return (size == 1) ? 0 : 1 + getMaxDepth(size / 2);
}

double MinMax::recurseScore(double score_, int depth, std::pair<int, int> position, std::pair<int, int> direction)
{
    if (depth == 0)
        return score_;

    position.first += direction.first;
    position.second += direction.second;
    if (position.first > (_bitboard->getRowSize() - 1) || (position.second > _bitboard->getRowSize() - 1) || position.first < 0 || position.second < 0)
        return score_;
    depth--;
    score_ += recurseScore(score_, depth, position, direction);

    int color = _bitboard->getBit(position);
    if (color== 2)
        score_ += 5;

    return score_;
}

double MinMax::updateScore(std::pair<int, int> position)
{
    double score = 0;
    int depth = 5;
    if (_bitboard->getBit(position)!= 0)
        return 0;
    score = recurseScore(score, depth--, position, std::make_pair(-1,0)); //Leftx
    score = recurseScore(score, depth--, position, std::make_pair(0,-1)); //Top
    score = recurseScore(score, depth--, position, std::make_pair(1,0)); //Right
    score = recurseScore(score, depth--, position, std::make_pair(0,1)); //Bottom
    score = recurseScore(score, depth--, position, std::make_pair(-1,-1)); //Top Left
    score = recurseScore(score, depth--, position, std::make_pair(1,-1)); //Top Right
    score = recurseScore(score, depth--, position, std::make_pair(1,1)); //Bottom Right
    score = recurseScore(score, depth--, position, std::make_pair(-1,1)); //Bottom Left
    return score;
}

void MinMax::displayScore()
{
    std::vector<std::bitset<2>> board_ = _bitboard->getBitboard();
    int x_size = 0;
    int y_size = 0;
    int board_count_ = 0;

    for (y_size = 0; y_size < _bitboard->getRowSize();y_size++) {
        for (x_size = 0; x_size < _bitboard->getRowSize(); x_size++)
            std::cout << "|" << (int)updateScore(std::make_pair(x_size, y_size)) << "|";
        board_count_++;
        std::cout << std::endl;
    }
}

void MinMax::getScoreInMap()
{
    std::vector<std::bitset<2>> board_ = _bitboard->getBitboard();
    int x_size = 0;
    int y_size = 0;
    int board_count_ = 0;

    for (y_size = 0; y_size < _bitboard->getRowSize();y_size++) {
        for (x_size = 0; x_size < _bitboard->getRowSize(); x_size++)
            _scores.push_back(node{updateScore(std::make_pair(x_size, y_size)), (int)_scores.size() + 1,std::make_pair(x_size, y_size)});
        board_count_++;
    }
}

std::pair<int, int> MinMax::nodeToPosition(node my_node)
{
    return my_node.position;
}

std::pair<int, int> MinMax::playTurn()
{
    getScoreInMap();
    int size = _scores.size();
    int maxDepth = getMaxDepth(size);

    node result = findBestMove(0, 0, true, maxDepth);
    std::pair<int, int> position = nodeToPosition(result);

    // std::cout << "Result : " << result.score << std::endl;

    // std::cout << "SUGGEST [" << position.first << "] [" << position.second << "]" << std::endl;
    return std::make_pair(position.first, position.second);
}