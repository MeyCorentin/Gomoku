#include "../includes/bitboard.hpp"

Bitboard::Bitboard()  {}
Bitboard::Bitboard(int size) : board_(size * size), size_(size * size), row_size_(size) {}

void Bitboard::reSize(int size)
{
    board_ = std::vector<std::bitset<2>>(size * size);
    for (auto& bitset : board_) {
        bitset.reset();
    }
    size_ = size * size;
    row_size_ = size;
}

Bitboard::Bitboard(const Bitboard& other) {
    board_ = other.board_;
    size_ = other.size_;
    row_size_ = other.row_size_;
}


void Bitboard::setBit(std::pair<int, int> position, int color) {
    int index = position.first + position.second * row_size_;
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

int Bitboard::getBit(std::pair<int, int> position)const {
    int index = position.first + position.second * row_size_;
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
            int color = getBit(std::make_pair(j, i));
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