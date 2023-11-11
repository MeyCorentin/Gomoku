#include "../includes/parser.hpp"

Parser::Parser()
{

}

void Parser::Compute(Bitboard &arg_board, std::string &arg_input)
{
    std::getline(std::cin, arg_input);
    if (arg_input.substr(0, 5) == "START") {
        int n = std::stoi(arg_input.substr(6));
        std::cout << "size: " << n << " x " << n;
        arg_board.reSize(n);
    }
}