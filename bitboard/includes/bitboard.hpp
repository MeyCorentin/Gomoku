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

        int getSize();

        int getRowSize();

        void play(std::pair<int,int> position, int value);

        std::pair<int, int> getPosition(int index);

        int getIndex(std::pair<int, int> position);

    private:
        std::vector<uint64_t> bitboard_;
        int size_;
        int row_size_;

        Bitboard();

        Bitboard(const Bitboard&) = delete;
        Bitboard& operator=(const Bitboard&) = delete;
};
