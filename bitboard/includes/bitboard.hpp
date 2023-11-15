#include <vector>
#include <cstdint>
<<<<<<< HEAD
#include <string>
=======
>>>>>>> 3445f915f06ce1367c0ade49869e3736d28648e7
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

        void play(int x_position, int y_position, int value);

    private:
        std::vector<uint64_t> bitboard_;
        int size_;
        int row_size_;

        Bitboard();

        Bitboard(const Bitboard&) = delete;
        Bitboard& operator=(const Bitboard&) = delete;
};
