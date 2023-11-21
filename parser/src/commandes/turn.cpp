#include "../../includes/parser.hpp"

void Parser::C_turn(Bitboard &arg_board, std::string &arg_input)
{
    MinMax min_max(&arg_board);
    std::istringstream iss(arg_input);
    std::string cmd;
    char delimiter;
    int x, y;
    iss >> cmd >> x >> delimiter >> y;
    arg_board.setBit(std::make_pair(x, y), 0);
    std::pair<int, int> brain_play = min_max.playTurn();
    arg_board.setBit(brain_play , 1);
    std::cout <<brain_play.first <<"," << brain_play.second << std::endl;
}