#include "../../includes/parser.hpp"
#include "error.cpp"

void Parser::C_start(Bitboard &arg_board, std::string &arg_input)
{
    int n = std::stoi(arg_input.substr(6));
    if (n <= 0 )
        C_error();
    else
        arg_board.reSize(n);
}