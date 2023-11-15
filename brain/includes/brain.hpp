#include <iostream>

#pragma once

#include "../../bitboard/includes/bitboard.hpp"

class Brain {
    public:
        Brain();
        void Compute(Bitboard &arg_board, std::string &input);
};