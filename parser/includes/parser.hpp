#include <iostream>
#include <string>
#include <sstream>
#pragma once
#include "../../bitboard/includes/bitboard.hpp"

class Parser {
    public:
        Parser();
        void Compute(Bitboard &arg_board, std::string &arg_input);
};

