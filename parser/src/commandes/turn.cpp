#include "../../includes/parser.hpp"

void Parser::C_turn(Bitboard &arg_board, std::string &arg_input)
{
    std::istringstream iss(arg_input);
    std::string cmd;
    int x, y;
    iss >> cmd >> x >> y;
    arg_board.play(x, y, 1);
}