#include <iostream>
#pragma once
#include "../../bitboard/includes/bitboard.hpp"

class Parser {
    public:
        Parser();
        void Compute(Bitboard &arg_board, std::string &arg_input);
};

