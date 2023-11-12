#include "../includes/parser.hpp"

Parser::Parser()
{

}

void Parser::Compute(Bitboard &arg_board, std::string &arg_input)
{
    std::getline(std::cin, arg_input);
    if (arg_input.substr(0, 4) == "TURN") {
        std::istringstream iss(arg_input);
        std::string cmd;
        int x, y;
        iss >> cmd >> x >> y;
        arg_board.play(x, y, 1);
    }
    if (arg_input.substr(0, 5) == "START") {
        int n = std::stoi(arg_input.substr(6));
        arg_board.reSize(n);
    }
    if (arg_input.substr(0, 8) == "DISPLAY") {
        // arg_board.displayBoard();
        // arg_board.displayUseBoard();
        arg_board.display();
    }
}