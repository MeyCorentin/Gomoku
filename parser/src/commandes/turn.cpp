#include "../../includes/parser.hpp"

void Parser::C_turn(Bitboard &arg_board, std::string &arg_input)
{
    MinMax min_max(&arg_board);
    std::istringstream iss(arg_input);
    std::string cmd;
    int x, y;
    iss >> cmd >> x >> y;
    std::cout << "---" << std::endl;
    std::cout << x << "/" << y << std::endl;
    std::cout << "---" << std::endl;
    arg_board.setBit(x, y, 0);
    std::pair<int, int> result = min_max.playTurn();
    std::cout << "---" << std::endl;
    std::cout << result.first << "/" << result.second << std::endl;
    std::cout << "---" << std::endl;
    arg_board.setBit(result.first, result.second , 1);
}