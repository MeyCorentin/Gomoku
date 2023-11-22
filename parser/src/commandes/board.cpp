#include "../../includes/parser.hpp"

void Parser::C_board(Bitboard &arg_board, std::string &arg_input)
{
    if (arg_input.substr(0, 4) == "DONE") {
        on_board_creation = false;
        C_begin(arg_board, arg_input);
    }
    if (on_board_creation == true)
    {
        std::istringstream iss(arg_input);
        char delimiter;
        int x, y, value;
        iss >> x >> delimiter >> y >> delimiter >> value;
        arg_board.setBit(std::make_pair(x , y), value - 1);
    }
    if (arg_input.substr(0, 5) == "BOARD") {
        on_board_creation = true;
    }
}