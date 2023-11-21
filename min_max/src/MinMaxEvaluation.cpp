#include "../includes/MinMax.hpp"

bool MinMax::fourOpen(std::pair<int, int> position, std::pair<int,int> direction, bool attack)
{
    if (position.first - (direction.first) > (_bitboard->getRowSize()) ||
        (position.second - (direction.second ) > _bitboard->getRowSize()) ||
        position.first - (direction.first) < 0 ||
        position.second - (direction.second) < 0)
        return false;
    if (position.first + (direction.first * 4) > (_bitboard->getRowSize()) ||
        (position.second + (direction.second * 4) > _bitboard->getRowSize()) ||
        position.first + (direction.first * 4) < 0 ||
        position.second + (direction.second * 4) < 0)
        return false;
    if (
        _bitboard->getBit(std::make_pair(position.first - direction.first, position.second - direction.second)) == 0 &&
        pionNumberInDirection(position, direction, attack) == 3 &&
        _bitboard->getBit(std::make_pair(position.first + (direction.first * 4), position.second + (direction.second * 4))) == 0
        )
        return true;
    return false;
}

bool MinMax::fourClose(std::pair<int, int> position, std::pair<int,int> direction, bool attack)
{
    if (position.first - (direction.first) > (_bitboard->getRowSize()) ||
        (position.second - (direction.second) > _bitboard->getRowSize()) ||
        position.first - (direction.first) < 0 ||
        position.second - (direction.second) < 0)
        return false;
    if (position.first + (direction.first * 4) > (_bitboard->getRowSize()) ||
        (position.second + (direction.second * 4) > _bitboard->getRowSize()) ||
        position.first + (direction.first * 4) < 0 ||
        position.second + (direction.second * 4) < 0)
        return false;
    if (
        _bitboard->getBit(std::make_pair(position.first - direction.first, position.second - direction.second)) == (attack ? 1 : 2) &&
        pionNumberInDirection(position, direction, attack) == 3 &&
        _bitboard->getBit(std::make_pair(position.first + (direction.first * 4), position.second + (direction.second * 4))) == 0
        )
        return true;
    if (
        _bitboard->getBit(std::make_pair(position.first - direction.first, position.second - direction.second)) == 0 &&
        pionNumberInDirection(position, direction, attack) == 3 &&
        _bitboard->getBit(std::make_pair(position.first + (direction.first * 4), position.second + (direction.second * 4))) == (attack ? 1 : 2)
        )
        return true;
    return false;
}

bool MinMax::fourSplit(std::pair<int, int> position, std::pair<int,int> direction, bool attack)
{
    if (position.first - (direction.first) > (_bitboard->getRowSize()) ||
        (position.second - (direction.second) > _bitboard->getRowSize()) ||
        position.first - (direction.first) < 0 ||
        position.second - (direction.second) < 0)
        return false;
    if (position.first + (direction.first * 4) > (_bitboard->getRowSize()) ||
        (position.second + (direction.second * 4) > _bitboard->getRowSize()) ||
        position.first + (direction.first * 4) < 0 ||
        position.second + (direction.second * 4) < 0)
        return false;
    if (
        _bitboard->getBit(std::make_pair(position.first - direction.first, position.second - direction.second)) == (attack ? 1 : 2) &&
        pionNumberInDirection(position, direction, attack) == 2 &&
        _bitboard->getBit(std::make_pair(position.first + (direction.first * 3), position.second + (direction.second * 3))) == 0 &&
        _bitboard->getBit(std::make_pair(position.first + (direction.first * 4), position.second + (direction.second * 4))) ==  (attack ? 2 : 1)
        )
        return true;
    if (
        _bitboard->getBit(std::make_pair(position.first - direction.first, position.second - direction.second)) == 0 &&
        _bitboard->getBit(std::make_pair(position.first + direction.first, position.second + direction.second)) == 0 &&
        pionNumberInDirection(std::make_pair(position.first + direction.first, position.second + direction.second), direction, attack) == 3 &&
        _bitboard->getBit(std::make_pair(position.first + (direction.first * 5), position.second + (direction.second * 5))) == (attack ? 1 : 2)
        )
        return true;
    return false;
}

bool MinMax::threeSplit(std::pair<int, int> position, std::pair<int,int> direction, bool attack)
{
    if (position.first - (direction.first) > (_bitboard->getRowSize()) ||
        (position.second - (direction.second) > _bitboard->getRowSize()) ||
        position.first - (direction.first) < 0 ||
        position.second - (direction.second) < 0)
        return false;
    if (position.first + (direction.first * 4) > (_bitboard->getRowSize()) ||
        (position.second + (direction.second * 4) > _bitboard->getRowSize()) ||
        position.first + (direction.first * 4) < 0 ||
        position.second + (direction.second * 4) < 0)
        return false;
    if (
        _bitboard->getBit(std::make_pair(position.first - direction.first, position.second - direction.second)) == (attack ? 1 : 2) &&
        pionNumberInDirection(position, direction, attack) == 1 &&
        _bitboard->getBit(std::make_pair(position.first + (direction.first * 2), position.second + (direction.second * 2))) == 0 &&
        _bitboard->getBit(std::make_pair(position.first + (direction.first * 3), position.second + (direction.second * 3))) ==  (attack ? 2 : 1)
        )
        return true;
    if (
        _bitboard->getBit(std::make_pair(position.first - direction.first, position.second - direction.second)) == 0 &&
        _bitboard->getBit(std::make_pair(position.first + direction.first, position.second + direction.second)) == 0 &&
        pionNumberInDirection(std::make_pair(position.first + direction.first, position.second + direction.second), direction, attack) == 2 &&
        _bitboard->getBit(std::make_pair(position.first + (direction.first * 4), position.second + (direction.second * 4))) == (attack ? 1 : 2)
        )
        return true;
    return false;
}

bool MinMax::threeBlock(std::pair<int, int> position, std::pair<int,int> direction, bool attack)
{
    if (position.first - (direction.first * 2) > (_bitboard->getRowSize()) ||
        (position.second - (direction.second * 2) > _bitboard->getRowSize()) ||
        position.first - (direction.first * 2) < 0 ||
        position.second - (direction.second * 2) < 0)
        return false;
    if (position.first + (direction.first * 4) > (_bitboard->getRowSize()) ||
        (position.second + (direction.second * 4) > _bitboard->getRowSize()) ||
        position.first + (direction.first * 4) < 0 ||
        position.second + (direction.second * 4) < 0)
        return false;
    if (
        _bitboard->getBit(std::make_pair(position.first - direction.first, position.second - direction.second)) == 0 &&
        _bitboard->getBit(std::make_pair(position.first - (direction.first * 2), position.second - ( direction.second * 2))) == (attack ? 1 : 2) &&
        pionNumberInDirection(position, direction, attack) == 2 &&
        _bitboard->getBit(std::make_pair(position.first + (direction.first * 3), position.second + ( direction.second * 3))) == 0
        )
        return true;
    if (
        _bitboard->getBit(std::make_pair(position.first - direction.first, position.second - direction.second)) == 0 &&
        pionNumberInDirection(position, direction, attack) == 2 &&
        _bitboard->getBit(std::make_pair(position.first + (direction.first * 3), position.second + (direction.second * 3))) == 0 &&
        _bitboard->getBit(std::make_pair(position.first + (direction.first * 4), position.second + (direction.second * 4))) == (attack ? 1 : 2)
        )
        return true;
    return false;
}

bool MinMax::threeTwoOne(std::pair<int, int> position, std::pair<int,int> direction, bool attack)
{
    if (position.first - (direction.first) > (_bitboard->getRowSize()) ||
        (position.second - (direction.second) > _bitboard->getRowSize()) ||
        position.first - (direction.first) < 0 ||
        position.second - (direction.second) < 0)
        return false;
    if (position.first + (direction.first * 4) > (_bitboard->getRowSize()) ||
        (position.second + (direction.second * 4) > _bitboard->getRowSize()) ||
        position.first + (direction.first * 4) < 0 ||
        position.second + (direction.second * 4) < 0)
        return false;
    if (
        _bitboard->getBit(std::make_pair(position.first - direction.first, position.second - direction.second)) == 0 &&
        _bitboard->getBit(std::make_pair(position.first + direction.first, position.second + direction.second)) == (attack ? 2 : 1) &&
        _bitboard->getBit(std::make_pair(position.first + (direction.first * 2), position.second + ( direction.second * 2))) == 0 &&
        _bitboard->getBit(std::make_pair(position.first + (direction.first * 3), position.second + ( direction.second * 3))) == (attack ? 2 : 1) &&
        _bitboard->getBit(std::make_pair(position.first + (direction.first * 4), position.second + ( direction.second * 4))) == 0
        )
        return true;
    if (
        _bitboard->getBit(std::make_pair(position.first - direction.first, position.second - direction.second)) == 0 &&
        _bitboard->getBit(std::make_pair(position.first + direction.first, position.second + direction.second)) == 0 &&
        _bitboard->getBit(std::make_pair(position.first + (direction.first * 2), position.second + ( direction.second * 2))) == (attack ? 2 : 1) &&
        _bitboard->getBit(std::make_pair(position.first + (direction.first * 3), position.second + ( direction.second * 3))) == (attack ? 2 : 1) &&
        _bitboard->getBit(std::make_pair(position.first + (direction.first * 4), position.second + ( direction.second * 4))) == 0
        )
        return true;
    return false;
}


bool MinMax::threeClose(std::pair<int, int> position, std::pair<int,int> direction, bool attack)
{
    if (position.first - (direction.first) > (_bitboard->getRowSize()) ||
        (position.second - (direction.second) > _bitboard->getRowSize()) ||
        position.first - (direction.first) < 0 ||
        position.second - (direction.second) < 0)
        return false;
    if (position.first + (direction.first * 3) > (_bitboard->getRowSize()) ||
        (position.second + (direction.second * 3) > _bitboard->getRowSize()) ||
        position.first + (direction.first * 3) < 0 ||
        position.second + (direction.second * 3 ) < 0)
        return false;
    if (
        _bitboard->getBit(std::make_pair(position.first - direction.first, position.second - direction.second)) == (attack ? 1 : 2) &&
        pionNumberInDirection(position, direction, attack) == 2 &&
        _bitboard->getBit(std::make_pair(position.first + (direction.first * 3), position.second + (direction.second * 3))) == 0
        )
        return true;
    if (
        _bitboard->getBit(std::make_pair(position.first - direction.first, position.second - direction.second)) == 0 &&
        pionNumberInDirection(position, direction, attack) == 2 &&
        _bitboard->getBit(std::make_pair(position.first + (direction.first * 3), position.second + (direction.second * 3))) == (attack ? 1 : 2)
        )
        return true;
    return false;
}


bool MinMax::threeOpen(std::pair<int, int> position, std::pair<int,int> direction, bool attack)
{
    if (position.first - (direction.first) > (_bitboard->getRowSize()) ||
        (position.second - (direction.second)> _bitboard->getRowSize()) ||
        position.first - (direction.first) < 0 ||
        position.second - (direction.second) < 0)
        return false;
    if (position.first + (direction.first * 3) > (_bitboard->getRowSize()) ||
        (position.second + (direction.second * 3) > _bitboard->getRowSize()) ||
        position.first + (direction.first * 3) < 0 ||
        position.second + (direction.second * 3) < 0)
        return false;
    if (
        _bitboard->getBit(std::make_pair(position.first - direction.first, position.second - direction.second)) == 0 &&
        pionNumberInDirection(position, direction, attack) == 2 &&
        _bitboard->getBit(std::make_pair(position.first + (direction.first * 3), position.second + (direction.second * 3))) == 0
        )
        return true;
    return false;
}

bool MinMax::twoOpen(std::pair<int, int> position, std::pair<int,int> direction, bool attack)
{
    if (position.first - (direction.first) > (_bitboard->getRowSize()) ||
        (position.second - (direction.second) > _bitboard->getRowSize()) ||
        position.first - (direction.first) < 0 ||
        position.second - (direction.second) < 0)
        return false;
    if (position.first + (direction.first * 2) > (_bitboard->getRowSize()) ||
        (position.second + (direction.second * 2) > _bitboard->getRowSize()) ||
        position.first + (direction.first * 2) < 0 ||
        position.second + (direction.second * 2) < 0)
        return false;
    if (
        _bitboard->getBit(std::make_pair(position.first - direction.first, position.second - direction.second)) == 0 &&
        pionNumberInDirection(position, direction, attack) == 1 &&
        _bitboard->getBit(std::make_pair(position.first + (direction.first * 2), position.second + (direction.second * 2))) == 0
        )
        return true;
    return false;
}

bool MinMax::threeJump(std::pair<int, int> position, std::pair<int,int> direction, bool attack)
{

    if (position.first - (direction.first) > (_bitboard->getRowSize()) ||
        (position.second - (direction.second) > _bitboard->getRowSize()) ||
        position.first - (direction.first) < 0 ||
        position.second - (direction.second) < 0)
        return false;
    if (position.first + (direction.first * 5) > (_bitboard->getRowSize()) ||
        (position.second + (direction.second * 5) > _bitboard->getRowSize()) ||
        position.first + (direction.first * 5) < 0 ||
        position.second + (direction.second * 5) < 0)
        return false;
    if (
        _bitboard->getBit(std::make_pair(position.first - direction.first, position.second - direction.second)) == 0 &&
        _bitboard->getBit(std::make_pair(position.first + direction.first, position.second + direction.second)) == 0 &&
        _bitboard->getBit(std::make_pair(position.first + (direction.first * 2), position.second + (direction.second * 2))) == (attack ? 2 : 1) &&
        _bitboard->getBit(std::make_pair(position.first + (direction.first * 3), position.second + (direction.second * 3))) == 0 &&
        _bitboard->getBit(std::make_pair(position.first + (direction.first * 4), position.second + (direction.second * 4))) == (attack ? 2 : 1) &&
        _bitboard->getBit(std::make_pair(position.first + (direction.first * 5), position.second + (direction.second * 5))) == 0
        )
        return true;
    return false;
}

int MinMax::evaluateCell(std::pair<int, int> position, std::pair<int,int> direction, bool attack)
{
    int score = 0;
    if (fourOpen(position, direction, attack))
        score += 10000;
    if (fourClose(position, direction, attack))
        score += 1000;
    if (fourSplit(position, direction, attack))
        score += 1000;
    if (threeBlock(position, direction, attack))
        score += 1000;
    if (threeTwoOne(position, direction, attack))
        score += 1000;
    if (threeOpen(position, direction, attack))
        score += 1000;
    if (threeClose(position, direction, attack))
        score += 100;
    if (twoOpen(position, direction, attack))
        score += 100;
    if (threeSplit(position, direction, attack))
        score += 100;
    if (threeJump(position, direction, attack))
        score += 100;
    return score;
}

int MinMax::evaluatePosition(bool attack)
{
    int score = 0;

    std::vector<std::bitset<2>> board_ = _bitboard->getBitboard();
    int x_size = 0;
    int y_size = 0;
    int board_count_ = 0;
    std::pair<int, int> position;
    for (y_size = 0; y_size < _bitboard->getRowSize();y_size++) {
        for (x_size = 0; x_size < _bitboard->getRowSize(); x_size++)
        {
            position = std::make_pair(x_size, y_size);
            if (_bitboard->getBit(position) != (attack ? 2 : 1))
                continue;
            score += evaluateCell(position, std::make_pair(-1,0), attack); //Leftx
            score += evaluateCell(position, std::make_pair(0,-1), attack); //Top
            score += evaluateCell(position, std::make_pair(1,0), attack); //Right
            score += evaluateCell(position, std::make_pair(0,1), attack); //Bottom
            score += evaluateCell(position, std::make_pair(-1,-1), attack); //Top Left
            score += evaluateCell(position, std::make_pair(1,-1), attack); //Top Right
            score += evaluateCell(position, std::make_pair(1,1), attack); //Bottom Right
            score += evaluateCell(position, std::make_pair(-1,1), attack); //Bottom Left
        }
        board_count_++;
    }
    return score;
}