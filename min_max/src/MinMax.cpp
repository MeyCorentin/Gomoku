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
    if (result_defense.score > result_attack.score)
    {
        auto it = std::find(_scores_defense.begin(), _scores_defense.end(), result_defense);
        if (it != _scores_defense.end())
        {
            _scores_defense.erase(it);
        }
        result_defense.score = 0;
        return result_defense;
    }
    auto it = std::find(_scores_attack.begin(), _scores_attack.end(), result_attack);
    if (it != _scores_attack.end())
    {
        _scores_attack.erase(it);
    }
    result_attack.score = 0;
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


int MinMax::spaceFree(std::pair<int, int> position, std::pair<int,int> direction)
{
    position.first += direction.first;
    position.second += direction.second;
    if (position.first > (_bitboard->getRowSize() - 1) || (position.second > _bitboard->getRowSize() - 1) || position.first < 0 || position.second < 0)
        return 0;
    int color = _bitboard->getBit(position);
    if (color != 0)
        return 0;
    else
        return (1 + spaceFree(position, direction));

}

int MinMax::pionNumberInDirection(std::pair<int, int> position, std::pair<int,int> direction)
{
    position.first += direction.first;
    position.second += direction.second;
    if (position.first > (_bitboard->getRowSize() - 1) || (position.second > _bitboard->getRowSize() - 1) || position.first < 0 || position.second < 0)
        return 0;
    int color = _bitboard->getBit(position);
    if (color != (is_begin ? 1 : 2))
        return 0;
    else
    {
        return (1 + pionNumberInDirection(position, direction));
    }

}


int MinMax::endInDiretion(std::pair<int, int> position, std::pair<int,int> direction)
{
    position.first += direction.first;
    position.second += direction.second;
    int color = _bitboard->getBit(position);
    if (color == (is_begin ? 1 : 2))
        return (currentLineNumber(position, direction));
    return  color;
}


int MinMax::currentLineNumber(std::pair<int, int> position, std::pair<int,int> direction)
{
    int pion_number = pionNumberInDirection(position, std::make_pair(-direction.first, -direction.second)) +  pionNumberInDirection(position, std::make_pair(direction.first, direction.second));;

    return  pion_number;
}

int MinMax::maxPossibleLine(std::pair<int, int> position, std::pair<int,int> direction, bool attack)
{
    int pion_number = pionNumberInDirection(position, std::make_pair(-direction.first, -direction.second));
    int space_free = spaceFree(position, direction);
    return pion_number + space_free;
}


int MinMax::countSpaceFree()
{
    std::vector<std::bitset<2>> board_ = _bitboard->getBitboard();
    int x_size = 0;
    int y_size = 0;
    int count = 0;
    for (y_size = 0; y_size < _bitboard->getRowSize();y_size++) {
        for (x_size = 0; x_size < _bitboard->getRowSize(); x_size++)
        {
            if (_bitboard->getBit(std::make_pair(x_size, y_size)) == 0)
                count++;

        }
    }
    return count;
}

int MinMax::updateScore(std::pair<int, int> position, bool attack)
{
    int score = 0;
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
            if (_bitboard->getBit(std::make_pair(x_size, y_size)) != 0)
                continue;
            _scores_defense.push_back(node{(float)updateScore(std::make_pair(x_size, y_size), false), (int)_scores_defense.size() + 1,std::make_pair(x_size, y_size)});
            _scores_attack.push_back(node{(float)updateScore(std::make_pair(x_size, y_size), true), (int)_scores_attack.size() + 1,std::make_pair(x_size, y_size)});
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
    std::vector<node> evaluation_defense;
    std::vector<node> evaluation_attack;
    for (int k = 0; k != countSpaceFree(); k++)
        result.push_back(findBestMove());

    for (auto& node_ : result)
    {
        Bitboard temp_board_1(*_bitboard);
        MinMax temp_minmax_1(&temp_board_1);
        temp_minmax_1.is_begin = is_begin;
        temp_minmax_1._bitboard->setBit(node_.position, is_begin ? 1 : 0);

        Bitboard temp_board_2(*_bitboard);
        MinMax temp_minmax_2(&temp_board_2);
        temp_minmax_2.is_begin = !is_begin;
        temp_minmax_2._bitboard->setBit(node_.position,  is_begin ? 0 : 1);

        evaluation_attack.push_back(node{temp_minmax_1.evaluatePosition(), (int)evaluation_attack.size() + 1, node_.position});
        evaluation_defense.push_back(node{temp_minmax_2.evaluatePosition(), (int)evaluation_defense.size() + 1, node_.position});
    }
    auto max_eval_attack = std::max_element(evaluation_attack.begin(), evaluation_attack.end(), [](const node& a, const node& b) {
        return a.score < b.score;
    });

    auto max_eval_defense = std::max_element(evaluation_defense.begin(), evaluation_defense.end(), [](const node& a, const node& b) {
        return a.score < b.score;
    });

    if (is_begin)
    {
        if (evaluation_attack[std::distance(evaluation_attack.begin(), max_eval_attack)].score >= evaluation_defense[std::distance(evaluation_defense.begin(), max_eval_defense)].score)
            return evaluation_attack[std::distance(evaluation_attack.begin(), max_eval_attack)].position;
        else
            return evaluation_defense[std::distance(evaluation_defense.begin(), max_eval_defense)].position;
    } else {
        if (evaluation_attack[std::distance(evaluation_attack.begin(), max_eval_attack)].score >= evaluation_defense[std::distance(evaluation_defense.begin(), max_eval_defense)].score)
            return evaluation_attack[std::distance(evaluation_attack.begin(), max_eval_attack)].position;
        else
            return evaluation_defense[std::distance(evaluation_defense.begin(), max_eval_defense)].position;
    }
}