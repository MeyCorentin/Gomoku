#include "../includes/MinMax.hpp"

bool MinMax::fourOpen(std::pair<int, int> position, std::pair<int,int> direction)
{
    if (position.first - (direction.first) > (_bitboard->getRowSize()) ||
        (position.second - (direction.second ) > _bitboard->getRowSize()) ||
        position.first - (direction.first) <= 0 ||
        position.second - (direction.second) <= 0)
        return false;
    if (position.first + (direction.first * 4) >= (_bitboard->getRowSize()) ||
        (position.second + (direction.second * 4) >= _bitboard->getRowSize()) ||
        position.first + (direction.first * 4) <= 0 ||
        position.second + (direction.second * 4) <= 0)
        return false;
    if (
        _bitboard->getBit(std::make_pair(position.first - direction.first, position.second - direction.second)) == 0 &&
        _bitboard->getBit(std::make_pair(position.first, position.second )) == (is_begin ? 1 : 2) &&
        pionNumberInDirection(position, direction) == 3 &&
        _bitboard->getBit(std::make_pair(position.first + (direction.first * 4), position.second + (direction.second * 4))) == 0
        )
        return true;
    return false;
}


bool MinMax::fiveEnd(std::pair<int, int> position, std::pair<int,int> direction)
{
    if (
        _bitboard->getBit(std::make_pair(position.first , position.second)) == (is_begin ? 1 : 2) &&
        pionNumberInDirection(position, direction) == 4
    ) {
        return true;
    }
    return false;
}


bool MinMax::fourClose(std::pair<int, int> position, std::pair<int,int> direction)
{
    if (
        (position.first - (direction.first) >= (_bitboard->getRowSize()) ||
        (position.second - (direction.second) >= _bitboard->getRowSize()) ||
        position.first - (direction.first) <= 0 ||
        position.second - (direction.second) <= 0) &&
        pionNumberInDirection(position, direction) == 4 &&
        _bitboard->getBit(std::make_pair(position.first , position.second)) == 0
        )
        return true;

    if (
        (position.first + (direction.first * 5) > (_bitboard->getRowSize()) ||
        (position.second + (direction.second * 5) > _bitboard->getRowSize()) ||
        position.first + (direction.first * 5) < 0 ||
        position.second + (direction.second * 5) < 0) &&
        pionNumberInDirection(position, direction) == 4 &&
        _bitboard->getBit(std::make_pair(position.first , position.second)) == 0
        )
        return true;
    if (
        position.first - (direction.first) > (_bitboard->getRowSize()) ||
        (position.second - (direction.second) > _bitboard->getRowSize()) ||
        position.first - (direction.first) < 0 ||
        position.second - (direction.second) < 0
        )
        return false;

    if (
        position.first + (direction.first * 5) >= (_bitboard->getRowSize()) ||
        (position.second + (direction.second * 5) >= _bitboard->getRowSize()) ||
        position.first + (direction.first * 5) < 0 ||
        position.second + (direction.second * 5) < 0
        )
        return false;
    if (
        _bitboard->getBit(std::make_pair(position.first + (direction.first * 5), position.second + (direction.second * 5))) == (is_begin ? 2 : 1) &&
        pionNumberInDirection(position, direction) == 4 &&
        _bitboard->getBit(std::make_pair(position.first , position.second)) == 0
        )
        return true;
    if (
        _bitboard->getBit(std::make_pair(position.first + (direction.first * 5), position.second + (direction.second * 5))) == 0 &&
        pionNumberInDirection(position, direction) == 4 &&
        _bitboard->getBit(std::make_pair(position.first , position.second)) == (is_begin ? 2 : 1)
        )
        return true;
    return false;
}

bool MinMax::fourSplit(std::pair<int, int> position, std::pair<int,int> direction)
{
    if (position.first - (direction.first) > (_bitboard->getRowSize()) ||
        (position.second - (direction.second) > _bitboard->getRowSize()) ||
        position.first - (direction.first) < 0 ||
        position.second - (direction.second) < 0)
        return false;
    if (position.first + (direction.first * 5) >= (_bitboard->getRowSize()) ||
        (position.second + (direction.second * 5) >= _bitboard->getRowSize()) ||
        position.first + (direction.first * 5) < 0 ||
        position.second + (direction.second * 5) < 0)
        return false;
    if (
        _bitboard->getBit(std::make_pair(position.first - direction.first, position.second - direction.second)) == (is_begin ? 1 : 2) &&
        pionNumberInDirection(position, direction) == 2 &&
        _bitboard->getBit(std::make_pair(position.first + (direction.first * 3), position.second + (direction.second * 3))) == 0 &&
        _bitboard->getBit(std::make_pair(position.first + (direction.first * 4), position.second + (direction.second * 4))) ==  (is_begin ? 2 : 1)
        )
        return true;
    if (
        _bitboard->getBit(std::make_pair(position.first - direction.first, position.second - direction.second)) == 0 &&
        _bitboard->getBit(std::make_pair(position.first + direction.first, position.second + direction.second)) == 0 &&
        pionNumberInDirection(std::make_pair(position.first + direction.first, position.second + direction.second), direction) == 3 &&
        _bitboard->getBit(std::make_pair(position.first + (direction.first * 5), position.second + (direction.second * 5))) == (is_begin ? 1 : 2)
        )
        return true;
    return false;
}

bool MinMax::threeTwoOneBlock(std::pair<int, int> position, std::pair<int,int> direction)
{
    if (position.first - (direction.first) > (_bitboard->getRowSize()) ||
        (position.second - (direction.second) > _bitboard->getRowSize()) ||
        position.first - (direction.first) < 0 ||
        position.second - (direction.second) < 0)
        return false;
    if (position.first + (direction.first * 5) >= (_bitboard->getRowSize()) ||
        (position.second + (direction.second * 5) >= _bitboard->getRowSize()) ||
        position.first + (direction.first * 5) < 0 ||
        position.second + (direction.second * 5) < 0)
        return false;
    if (
        _bitboard->getBit(std::make_pair(position.first - direction.first, position.second - direction.second)) == 0 &&
        _bitboard->getBit(std::make_pair(position.first + direction.first, position.second + direction.second)) == (is_begin ? 1 : 2) &&
        _bitboard->getBit(std::make_pair(position.first + (direction.first * 2), position.second + ( direction.second * 2))) == 0 &&
        _bitboard->getBit(std::make_pair(position.first + (direction.first * 3), position.second + ( direction.second * 3))) == (is_begin ? 1 : 2) &&
        _bitboard->getBit(std::make_pair(position.first + (direction.first * 4), position.second + ( direction.second * 4))) == (is_begin ? 1 : 2) &&
        _bitboard->getBit(std::make_pair(position.first + (direction.first * 5), position.second + ( direction.second * 5))) == (is_begin ? 2 : 1)
        )
        return true;
    return false;
}

bool MinMax::threeBlock(std::pair<int, int> position, std::pair<int,int> direction)
{
    if (position.first - (direction.first * 2) > (_bitboard->getRowSize()) ||
        (position.second - (direction.second * 2) > _bitboard->getRowSize()) ||
        position.first - (direction.first * 2) < 0 ||
        position.second - (direction.second * 2) < 0)
        return false;
    if (position.first + (direction.first * 4) >= (_bitboard->getRowSize()) ||
        (position.second + (direction.second * 4) >= _bitboard->getRowSize()) ||
        position.first + (direction.first * 4) < 0 ||
        position.second + (direction.second * 4) < 0)
        return false;
    if (
        _bitboard->getBit(std::make_pair(position.first - direction.first, position.second - direction.second)) == 0 &&
        _bitboard->getBit(std::make_pair(position.first - (direction.first * 2), position.second - ( direction.second * 2))) == (is_begin ? 1 : 2) &&
        pionNumberInDirection(position, direction) == 2 &&
        _bitboard->getBit(std::make_pair(position.first + (direction.first * 3), position.second + ( direction.second * 3))) == 0
        )
        return true;
    if (
        _bitboard->getBit(std::make_pair(position.first - direction.first, position.second - direction.second)) == 0 &&
        pionNumberInDirection(position, direction) == 2 &&
        _bitboard->getBit(std::make_pair(position.first + (direction.first * 3), position.second + (direction.second * 3))) == 0 &&
        _bitboard->getBit(std::make_pair(position.first + (direction.first * 4), position.second + (direction.second * 4))) == (is_begin ? 1 : 2)
        )
        return true;
    return false;
}

bool MinMax::threeTwoOne(std::pair<int, int> position, std::pair<int,int> direction)
{
    if (position.first - (direction.first) > (_bitboard->getRowSize()) ||
        (position.second - (direction.second) > _bitboard->getRowSize()) ||
        position.first - (direction.first) < 0 ||
        position.second - (direction.second) < 0)
        return false;
    if (position.first + (direction.first * 4) >= (_bitboard->getRowSize()) ||
        (position.second + (direction.second * 4) >= _bitboard->getRowSize()) ||
        position.first + (direction.first * 4) < 0 ||
        position.second + (direction.second * 4) < 0)
        return false;
    if (
        _bitboard->getBit(std::make_pair(position.first - direction.first, position.second - direction.second)) == 0 &&
        _bitboard->getBit(std::make_pair(position.first + direction.first, position.second + direction.second)) == (is_begin ? 1 : 2) &&
        _bitboard->getBit(std::make_pair(position.first + (direction.first * 2), position.second + ( direction.second * 2))) == 0 &&
        _bitboard->getBit(std::make_pair(position.first + (direction.first * 3), position.second + ( direction.second * 3))) == (is_begin ? 1 : 2) &&
        _bitboard->getBit(std::make_pair(position.first + (direction.first * 4), position.second + ( direction.second * 4))) == (is_begin ? 1 : 2) &&
        _bitboard->getBit(std::make_pair(position.first + (direction.first * 5), position.second + ( direction.second * 5))) == 0
        )
        return true;
    return false;
}


bool MinMax::threeClose(std::pair<int, int> position, std::pair<int,int> direction)
{
    if (position.first - (direction.first) > (_bitboard->getRowSize()) ||
        (position.second - (direction.second) > _bitboard->getRowSize()) ||
        position.first - (direction.first) < 0 ||
        position.second - (direction.second) < 0)
        return false;
    if (position.first + (direction.first * 3) >= (_bitboard->getRowSize()) ||
        (position.second + (direction.second * 3) >= _bitboard->getRowSize()) ||
        position.first + (direction.first * 3) < 0 ||
        position.second + (direction.second * 3 ) < 0)
        return false;
    if (
        _bitboard->getBit(std::make_pair(position.first - direction.first, position.second - direction.second)) == (is_begin ? 2 : 1) &&
        _bitboard->getBit(std::make_pair(position.first , position.second )) == (is_begin ? 1 : 2) &&
        pionNumberInDirection(position, direction) == 2 &&
        _bitboard->getBit(std::make_pair(position.first + (direction.first * 3), position.second + (direction.second * 3))) == 0
        )
        return true;
    return false;
}


bool MinMax::threeOpen(std::pair<int, int> position, std::pair<int,int> direction)
{
    if (position.first - (direction.first) > (_bitboard->getRowSize()) ||
        (position.second - (direction.second) > _bitboard->getRowSize()) ||
        position.first - (direction.first) < 0 ||
        position.second - (direction.second) < 0)
        return false;
    if (position.first + (direction.first * 3) >= (_bitboard->getRowSize()) ||
        (position.second + (direction.second * 3) >= _bitboard->getRowSize()) ||
        position.first + (direction.first * 3) < 0 ||
        position.second + (direction.second * 3) < 0)
        return false;
    if (
        _bitboard->getBit(std::make_pair(position.first - direction.first, position.second - direction.second)) == 0 &&
        _bitboard->getBit(std::make_pair(position.first, position.second )) == (is_begin ? 1 : 2) &&
        pionNumberInDirection(position, direction) == 2 &&
        _bitboard->getBit(std::make_pair(position.first + (direction.first * 3), position.second + (direction.second * 3))) == 0
        )
        return true;
    return false;
}


bool MinMax::twoClose(std::pair<int, int> position, std::pair<int,int> direction)
{
    if (position.first - (direction.first) > (_bitboard->getRowSize()) ||
        (position.second - (direction.second) > _bitboard->getRowSize()) ||
        position.first - (direction.first) < 0 ||
        position.second - (direction.second) < 0)
            return false;
    if (position.first + (direction.first * 3) >= (_bitboard->getRowSize()) ||
        (position.second + (direction.second * 3) >= _bitboard->getRowSize()) ||
        position.first + (direction.first * 3) < 0 ||
        position.second + (direction.second * 3) < 0)
            return false;

    if (
        _bitboard->getBit(std::make_pair(position.first - direction.first, position.second - direction.second)) == (is_begin ? 2 : 1) &&
        _bitboard->getBit(std::make_pair(position.first , position.second )) ==  (is_begin ? 1 : 2) &&
        pionNumberInDirection(position, direction) == 1 &&
        _bitboard->getBit(std::make_pair(position.first + (direction.first * 2), position.second + (direction.second * 2))) == 0
        )
            return true;

    if (
        _bitboard->getBit(std::make_pair(position.first , position.second )) ==  0 &&
        pionNumberInDirection(position, direction) == 2 &&
        _bitboard->getBit(std::make_pair(position.first + (direction.first * 3), position.second + (direction.second * 3))) == (is_begin ? 2 : 1) 
        )
            return true;
    return false;
}


bool MinMax::twoOpen(std::pair<int, int> position, std::pair<int,int> direction)
{
    if (position.first - (direction.first) > (_bitboard->getRowSize()) ||
        (position.second - (direction.second) > _bitboard->getRowSize()) ||
        position.first - (direction.first) < 0 ||
        position.second - (direction.second) < 0)
        return false;
    if (position.first + (direction.first * 2) >= (_bitboard->getRowSize()) ||
        (position.second + (direction.second * 2) >= _bitboard->getRowSize()) ||
        position.first + (direction.first * 2) < 0 ||
        position.second + (direction.second * 2) < 0)
        return false;
    if (
        _bitboard->getBit(std::make_pair(position.first , position.second )) == 0 &&
        pionNumberInDirection(position, direction) == 2 &&
        _bitboard->getBit(std::make_pair(position.first + (direction.first * 3), position.second + (direction.second * 3))) == 0
        )
        return true;
    return false;
}

bool MinMax::threeJump(std::pair<int, int> position, std::pair<int,int> direction)
{

    if (position.first - (direction.first) >= (_bitboard->getRowSize()) ||
        (position.second - (direction.second) >= _bitboard->getRowSize()) ||
        position.first - (direction.first) < 0 ||
        position.second - (direction.second) < 0)
        return false;
    if (position.first + (direction.first * 5) >= (_bitboard->getRowSize()) ||
        (position.second + (direction.second * 5) >= _bitboard->getRowSize()) ||
        position.first + (direction.first * 5) < 0 ||
        position.second + (direction.second * 5) < 0)
        return false;
    if (
        _bitboard->getBit(std::make_pair(position.first - direction.first, position.second - direction.second)) == 0 &&
        _bitboard->getBit(std::make_pair(position.first + direction.first, position.second + direction.second)) == (is_begin ? 1 : 2) &&
        _bitboard->getBit(std::make_pair(position.first + (direction.first * 2), position.second + (direction.second * 2))) == 0 &&
        _bitboard->getBit(std::make_pair(position.first + (direction.first * 3), position.second + (direction.second * 3))) == (is_begin ? 1 : 2) &&
        _bitboard->getBit(std::make_pair(position.first + (direction.first * 4), position.second + (direction.second * 4))) == 0 &&
        _bitboard->getBit(std::make_pair(position.first + (direction.first * 5), position.second + (direction.second * 5))) == (is_begin ? 1 : 2) &&
        _bitboard->getBit(std::make_pair(position.first + (direction.first * 6), position.second + (direction.second * 6))) == 0
        )
        return true;
    return false;
}

//! TODO : FAIRE UNE LISTE AU LIEU DE INT
int MinMax::evaluateCell(std::pair<int, int> position, std::pair<int,int> direction)
{
    int score = 0;
    if (fiveEnd(position, direction))
    {
        score += -300000;
        // std::cout << "fiveEnd" << std::endl;
    }
    if (fourOpen(position, direction))
    {
        score += 30000;
        // std::cout << "fourOpen" << std::endl;
    }
    if (fourClose(position, direction))
    {
        score += 3000;
        // std::cout << "fourClose" << std::endl;
    }
    if (threeOpen(position, direction))
    {
        score += 300;
        // std::cout << "threeOpen" << std::endl;
    }
    if (fourSplit(position, direction))
    {
        score += 30;
        // std::cout << "fourSplit" << std::endl;
    }
    if (threeBlock(position, direction))
    {
        score += 30;
        // std::cout << "threeBlock" << std::endl;
    }
    if (threeTwoOne(position, direction))
    {
        score += 30;
        // std::cout << "threeTwoOne" << std::endl;
    }
    if (threeClose(position, direction))
    {
        score += 30;
        // std::cout << "threeClose" << std::endl;
    }
    if (threeTwoOneBlock(position, direction))
    {
        score += 3;
        // std::cout << "threeTwoOneBlock" << std::endl;
    }
    if (threeJump(position, direction))
    {
        score += 3;
        // std::cout << "threeJump" << std::endl;
    }
    if (twoOpen(position, direction))
    {
        score += 2;
        // std::cout << "twoOpen" << std::endl;
    }
    if (twoClose(position, direction))
    {
        score += 1;
        // std::cout << "twoClose" << std::endl;
    }
    return score;
}


int MinMax::evaluatePosition()
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
            score += evaluateCell(position, std::make_pair(-1,0)); //Leftx
            score += evaluateCell(position, std::make_pair(0,-1)); //Top
            score += evaluateCell(position, std::make_pair(1,0)); //Right
            score += evaluateCell(position, std::make_pair(0,1)); //Bottom
            score += evaluateCell(position, std::make_pair(-1,-1)); //Top Left
            score += evaluateCell(position, std::make_pair(1,-1)); //Top Right
            score += evaluateCell(position, std::make_pair(1,1)); //Bottom Right
            score += evaluateCell(position, std::make_pair(-1,1)); //Bottom Left
        }
        board_count_++;
    }
    return score;
}