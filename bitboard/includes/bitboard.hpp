#include <vector>
#include <cstdint>
#include <string>
#include <iostream>
#include <bitset>
#pragma once

class Bitboard {
    std::vector<std::bitset<2>> board_;
    int size_;
    int row_size_;

    public:

    Bitboard();
    Bitboard(int size);

    void reSize(int size);
    void setBit(int x, int y, int color);
    int getSize();
    int getRowSize();
    std::vector<std::bitset<2>> getBitboard();

    int getBit(int x, int y) const;

    void displayBoard();
};