#include <vector>
#include <cstdint>
#include <string>
#include <iostream>
#include <bitset>
#pragma once

class Bitboard {

    public:
    int size_;
    int row_size_;
    int turn_played = 0;
    std::vector<std::bitset<2>> board_;

    Bitboard();
    Bitboard(int size);

    void reSize(int size);
    void setBit(std::pair<int, int> position, int color);
    int getSize();
    int getRowSize();
    std::vector<std::bitset<2>> getBitboard();

    Bitboard(const Bitboard& other);

    int getBit(std::pair<int, int> position) const;

    void displayBoard();
};