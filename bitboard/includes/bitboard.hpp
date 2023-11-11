#include <vector>
#include <cstdint>

#pragma once

class Bitboard {
    public:
        static Bitboard& getInstance();

        std::vector<uint64_t>& getBitboard();

        void reSize(int arg_size);

    private:
        std::vector<uint64_t> bitboard_;

        Bitboard();

        Bitboard(const Bitboard&) = delete;
        Bitboard& operator=(const Bitboard&) = delete;
};
