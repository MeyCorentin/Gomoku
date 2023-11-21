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
    node result_attack = *_scores_attack.begin();
    node result_defense = *_scores_defense.begin();
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
    {
        auto it = std::find(_scores_defense.begin(), _scores_defense.end(), result_defense);
        if (it != _scores_defense.end())
        {
            _scores_defense.erase(it);
        }
        return result_defense;
    }
    auto it = std::find(_scores_attack.begin(), _scores_attack.end(), result_attack);
    if (it != _scores_attack.end())
    {
        _scores_attack.erase(it);
    }
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
    int color = _bitboard->getBit(position);
    if (color == 0 || color != ( (attack ? 1 : 2 )))
        return score_;

    depth--;
    score_ += ((recurseScore(score_, depth, position, direction, attack)) * (6 - depth)) + 100;
    return score_;
}


int MinMax::spaceFree(std::pair<int, int> position, std::pair<int,int> direction, bool attack)
{
    position.first += direction.first;
    position.second += direction.second;
    if (position.first > (_bitboard->getRowSize() - 1) || (position.second > _bitboard->getRowSize() - 1) || position.first < 0 || position.second < 0)
        return 0;
    int color = _bitboard->getBit(position);
    if (color != 0)
        return 0;
    else
        return (1 + spaceFree(position, direction, attack));

}

int MinMax::pionNumberInDirection(std::pair<int, int> position, std::pair<int,int> direction, bool attack)
{
    position.first += direction.first;
    position.second += direction.second;
    if (position.first > (_bitboard->getRowSize() - 1) || (position.second > _bitboard->getRowSize() - 1) || position.first < 0 || position.second < 0)
        return 0;
    int color = _bitboard->getBit(position);
    if (color != (attack? 2 : 1))
        return 0;
    else
        return (1 + pionNumberInDirection(position, direction, attack));

}

int MinMax::maxPossibleLine(std::pair<int, int> position, std::pair<int,int> direction, bool attack)
{
    int pion_number = pionNumberInDirection(position, std::make_pair(-direction.first, -direction.second), attack);
    int space_free = spaceFree(position, direction, attack);
    return pion_number + space_free;
}

double MinMax::updateScore(std::pair<int, int> position, bool attack)
{
    double score = 0;
    int depth = 5;
    if (_bitboard->getBit(position) != 0)
        return 0;
    int max_possible = 0;
    max_possible = maxPossibleLine(position, std::make_pair(-1,0), attack);
    score += recurseScore(0, depth, position, std::make_pair(-1,0), attack) -5 + max_possible; //Leftx

    max_possible = maxPossibleLine(position, std::make_pair(0,-1), attack);
    score += recurseScore(0, depth, position, std::make_pair(0,-1), attack) -5 + max_possible; //Top

    max_possible = maxPossibleLine(position, std::make_pair(1,0), attack);
    score += recurseScore(0, depth, position, std::make_pair(1,0), attack) -5 + max_possible; //Right

    max_possible = maxPossibleLine(position, std::make_pair(0,1), attack);
    score += recurseScore(0, depth, position, std::make_pair(0,1), attack) -5 + max_possible; //Bottom

    max_possible = maxPossibleLine(position, std::make_pair(-1,-1), attack);
    score += recurseScore(0, depth, position, std::make_pair(-1,-1), attack) - 5 + max_possible; //Top Left

    max_possible = maxPossibleLine(position, std::make_pair(1,-1), attack);
    score += recurseScore(0, depth, position, std::make_pair(1,-1), attack) - 5 + max_possible; //Top Right

    max_possible = maxPossibleLine(position, std::make_pair(1,1), attack);
    score += recurseScore(0, depth, position, std::make_pair(1,1), attack) - 5 + max_possible; //Bottom Right

    max_possible = maxPossibleLine(position, std::make_pair(-1,1), attack);
    score += recurseScore(0, depth, position, std::make_pair(-1,1), attack) - 5 + max_possible; //Bottom Left
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

    std::vector<node> result;
    std::vector<int> evaluation;
    for (int k= 0; k != 10 ; k++)
        result.push_back(findBestMove());

    for (auto& node : result)
    {
        Bitboard temp_board;
        temp_board.reSize(_bitboard->getRowSize());
        MinMax temp_minmax(&temp_board);
        temp_minmax._bitboard->setBit(node.position, 2);
        evaluation.push_back(temp_minmax.evaluatePosition(true));
    }

    auto max_eval = std::max_element(evaluation.begin(), evaluation.end());
    int max_index = std::distance(evaluation.begin(), max_eval);
    return result[max_index].position;
}