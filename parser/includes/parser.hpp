#include <iostream>
#include <string>
#include <sstream>

#pragma once

#include "../../bitboard/includes/bitboard.hpp"

class Parser {
    public:
        Parser();
        void Compute(Bitboard &arg_board, std::string &arg_input);
    private:
        bool on_board_creation = false;
        void C_start(Bitboard &arg_board, std::string &arg_input);
        void C_turn(Bitboard &arg_board, std::string &arg_input);
        void C_board(Bitboard &arg_board, std::string &arg_input);
};

