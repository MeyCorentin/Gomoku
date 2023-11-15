#include <vector>
#include <cstdint>
#include <string>
#include <iostream>

#pragma once

class Bitboard {
    public:
        static Bitboard& getInstance();

        std::vector<uint64_t>& getBitboard();

        void reSize(int arg_size);


        void displayBoard();

        void displayUseBoard();

        void display();

        void play(int x_position, int y_position, int value);

    private:
        std::vector<uint64_t> bitboard_;
        int size_;
        int row_size_;

        Bitboard();

        Bitboard(const Bitboard&) = delete;
        Bitboard& operator=(const Bitboard&) = delete;
};
