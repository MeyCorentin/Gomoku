#include "../../includes/parser.hpp"

void Parser::C_turn(Bitboard &arg_board, std::string &arg_input)
{
    MinMax min_max(&arg_board);
    std::istringstream iss(arg_input);
    std::string cmd;
    int x, y;
    iss >> cmd >> x >> y;
    arg_board.play(std::make_pair(x,y), 0);
    arg_board.play(min_max.playTurn(), 1);
}