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
    bitboard_.resize(((arg_size/64) + 1) * 2, 0);
}