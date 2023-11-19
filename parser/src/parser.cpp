#include "../includes/parser.hpp"

Parser::Parser()
{

}

void Parser::Compute(Bitboard &arg_board, std::string &arg_input)
{
    std::getline(std::cin, arg_input);
    if (on_board_creation == true || arg_input.substr(0, 5) == "BOARD" || arg_input.substr(0, 4) == "DONE") {
        C_board(arg_board, arg_input);
        return;
    }
    if (arg_input.substr(0, 4) == "TURN") {
        C_turn(arg_board, arg_input);
        return;
    }
    if (arg_input.substr(0, 5) == "START") {
        C_start(arg_board, arg_input);
        return;
    }
    if (arg_input.substr(0, 5) == "BEGIN") {
        C_begin(arg_board, arg_input);
        return;
    }
    if (arg_input.substr(0, 8) == "DISPLAY") {
        // arg_board.displayBoard();
        // arg_board.displayUseBoard();
        arg_board.displayBoard();
        return;
    }
}