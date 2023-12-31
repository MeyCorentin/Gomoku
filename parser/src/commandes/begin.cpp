#include "../../includes/parser.hpp"

void Parser::C_begin(Bitboard &arg_board, std::string &arg_input)
{
    MinMax min_max(&arg_board);
    min_max.is_begin = true;
    is_begin = true;
    std::pair<int, int> brain_play = min_max.playTurn();
    arg_board.setBit(brain_play , 0);
    std::cout <<brain_play.first <<"," << brain_play.second << std::endl;
}