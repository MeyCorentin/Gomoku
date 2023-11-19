#include "../includes/MinMax.hpp"

MinMax::MinMax(Bitboard *bitboard)
{
    _bitboard = bitboard;
    _scores_attack = {};
    _scores_defense = {};
}

MinMax::~MinMax()
{

}

node MinMax::findBestMove()
{
    node result_attack{1,1,std::make_pair(1, 1)};
    node result_defense{1,1,std::make_pair(1, 1)};
    for (auto temp: _scores_attack)
    {
        if (temp.score > result_attack.score)
        {
            result_attack.score = temp.score;
            result_attack.i = temp.i;
            result_attack.position = temp.position;
        }
    }
    for (auto temp: _scores_defense)
    {
        if (temp.score > result_defense.score)
        {
            result_defense.score = temp.score;
            result_defense.i = temp.i;
            result_defense.position = temp.position;
        }
    }
    if (result_defense.score >= result_attack.score)
        return result_defense;
    return result_attack;
}

int MinMax::getMaxDepth(int size)
{
    return (size == 1) ? 0 : 1 + getMaxDepth(size / 2);
}

double MinMax::recurseScore(double score_, int depth, std::pair<int, int> position, std::pair<int, int> direction, bool attack)
{
    if (depth == 0)
        return score_;

    position.first += direction.first;
    position.second += direction.second;
    if (position.first > (_bitboard->getRowSize() - 1) || (position.second > _bitboard->getRowSize() - 1) || position.first < 0 || position.second < 0)
        return score_;
    depth--;
    int color = _bitboard->getBit(position);
    if (color == 0 || color != ( (attack ? 1 : 2 )))
        return score_;

    score_ += (recurseScore(score_, depth, position, direction, attack)) * (6 - depth);
    score_ += 10;


    return score_;
}

double MinMax::updateScore(std::pair<int, int> position, bool attack)
{
    double score = 0;
    int depth = 5;
    if (_bitboard->getBit(position) != 0)
        return 0;
    score += recurseScore(0, depth, position, std::make_pair(-1,0), attack); //Leftx
    score += recurseScore(0, depth, position, std::make_pair(0,-1), attack); //Top
    score += recurseScore(0, depth, position, std::make_pair(1,0), attack); //Right
    score += recurseScore(0, depth, position, std::make_pair(0,1), attack); //Bottom
    score += recurseScore(0, depth, position, std::make_pair(-1,-1), attack); //Top Left
    score += recurseScore(0, depth, position, std::make_pair(1,-1), attack); //Top Right
    score += recurseScore(0, depth, position, std::make_pair(1,1), attack); //Bottom Right
    score += recurseScore(0, depth, position, std::make_pair(-1,1), attack); //Bottom Left
    return score;
}

void MinMax::displayScore()
{
    std::vector<std::bitset<2>> board_ = _bitboard->getBitboard();
    int x_size = 0;
    int y_size = 0;
    int board_count_ = 0;
    int attack_score = 0;
    int defense_score = 0;
    for (y_size = 0; y_size < _bitboard->getRowSize();y_size++) {
        for (x_size = 0; x_size < _bitboard->getRowSize(); x_size++)
        {
            defense_score = (int)updateScore(std::make_pair(x_size, y_size), false);
            attack_score =(int)updateScore(std::make_pair(x_size, y_size), true);
            if (defense_score >= attack_score)
                std::cout << "|" << defense_score << "|";
            else
                std::cout << "|" << attack_score << "|";
        }
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
        {
            _scores_defense.push_back(node{updateScore(std::make_pair(x_size, y_size), false), (int)_scores_defense.size() + 1,std::make_pair(x_size, y_size)});
            _scores_attack.push_back(node{updateScore(std::make_pair(x_size, y_size), true), (int)_scores_attack.size() + 1,std::make_pair(x_size, y_size)});
        }
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

    node result = findBestMove();

    // std::cout << "Result : " << result.score << std::endl;

    // std::cout << "SUGGEST [" << position.first << "] [" << position.second << "]" << std::endl;
    return std::make_pair(result.position.first, result.position.second);
}