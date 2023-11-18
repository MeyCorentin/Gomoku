#include "../includes/bitboard.hpp"

Bitboard::Bitboard()  {}
Bitboard::Bitboard(int size) : board_(size * size), size_(size * size), row_size_(size) {}

void Bitboard::reSize(int size)
{
    board_ = std::vector<std::bitset<2>>(size * size);
    size_ = size * size;
    row_size_ = size;
}
void Bitboard::setBit(int x, int y, int color) {
    int index = x + y * row_size_;
    board_[index].set(0, 1);
    board_[index].set(1, color);
}

int Bitboard::getSize()
{
    return size_;
}

int Bitboard::getRowSize()
{
    return row_size_;
}

std::vector<std::bitset<2>> Bitboard::getBitboard() {
    return board_;
}

int Bitboard::getBit(int x, int y)const {
    int index = x + y * row_size_;
    if (board_[index].test(0)) {
        if (board_[index].test(1)) {
            return 1; // case noire
        } else {
            return 2; // case blanche
        }
    } else {
        return 0; // case vide
    }
}

void Bitboard::displayBoard() {
    for (int i = 0; i < row_size_; i++) {
        for (int j = 0; j < row_size_; j++) {
            int color = getBit(i, j);
            if (color == 0) {
                std::cout << ". ";
            } else if (color == 1) {
                std::cout << "O ";
            } else {
                std::cout << "X ";
            }
        }
        std::cout << std::endl;
    }
}