#include <iostream>

#pragma once

class Brain {
    public:
        Brain();
        void Compute(Bitboard &arg_board, std::string &input);
};