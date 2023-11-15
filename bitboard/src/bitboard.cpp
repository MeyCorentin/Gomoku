#include "../includes/bitboard.hpp"

Bitboard::Bitboard() {
    bitboard_.resize(1, 0);
}

Bitboard& Bitboard::getInstance() {
    static Bitboard instance;
    return instance;
}

std::vector<uint64_t>& Bitboard::getBitboard() {
    return bitboard_;
}

void Bitboard::reSize(int arg_size) {
    row_size_ = arg_size;
    size_ = arg_size * arg_size;
    bitboard_.resize(((arg_size * arg_size/64) + 1) * 2, 0);
}

void Bitboard::displayBoard() {
    int temp_size_ = 0;
    int board_count_ = 0;
    for (; temp_size_ < size_;) {
        for (int i = 0; i < 64; i += 2) {
            if (temp_size_ >= size_)
                break;
            if (temp_size_ % row_size_ == 0)
                std::cout << std::endl;
            temp_size_++;
            uint64_t mask = 1ULL << i;
            if (bitboard_[board_count_] & mask) {
                std::cout << "1 ";
            } else {
                std::cout << "0 ";
            }
        }
        board_count_ = ((temp_size_ ) / 64) + 1;
    }
    std::cout << std::endl;
}

void Bitboard::displayUseBoard() {
    int temp_size_ = 0;
    int board_count_ = 0;
    for (; temp_size_ < size_;) {
        for (int i = 0; i < 64; i++) {
            if (temp_size_ >= size_)
                break;
            if (temp_size_ % row_size_ == 0)
                std::cout << std::endl;
            temp_size_++;
            uint64_t mask = 1ULL << i;
            if (bitboard_[board_count_] & mask) {
                std::cout << "1 ";
            } else {
                std::cout << "0 ";
            }
        }
        board_count_ = ((temp_size_ ) / 64) + 1;
    }
    std::cout << std::endl;
}


void Bitboard::display() {
    int temp_size_ = 0;
    int board_count_ = 0;
    for (; temp_size_ < size_;) {
        for (int i = 1; i <= 64; i+=2) {
            if (temp_size_ >= size_)
                break;
            if (temp_size_ % row_size_ == 0)
                std::cout << std::endl;
            temp_size_++;
            uint64_t mask_2 = 1ULL << (i +   1);
            if (bitboard_[board_count_] & mask_2)
            {
                uint64_t mask = 1ULL << i;
                if (bitboard_[board_count_] & mask) {
                    std::cout << "X ";
                } else{
                    std::cout << "O ";
                }
            } else {
                std::cout << ". ";
            }
        }
        board_count_++;
    }
    std::cout << std::endl;
}

void Bitboard::play(int x_position, int y_position, int value) {
    int total_position = (((y_position - 1) * row_size_) + x_position);
    int temp_size = 0;
    int board_count = 0;
    uint64_t mask;
    uint64_t mask_2;

    for (; temp_size < total_position * 2;) {
        for (int i = 1; i <= 64 ; i+=2) {
            temp_size++;
            if (temp_size == total_position) {
                mask = 1ULL << i;
                mask_2 = 1ULL << (i + 1);
                bitboard_[board_count] |= mask_2;
                if (value == 1)
                    bitboard_[board_count] |= mask;
            }
        }
        board_count++;
    }
}