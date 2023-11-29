#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <future>

#include "min_max/includes/MinMax.hpp"
#include "parser/includes/parser.hpp"

std::mutex IO_MUTEX;
std::string input;

std::atomic<bool> stop_bool(false);

void readInput(Parser *arg_parser, Bitboard *board_) {
    while (!stop_bool) {
        IO_MUTEX.lock();
        if (input.substr(0, 3) != "END")
            arg_parser->Compute(*board_, input);
        else
            stop_bool = true;
        IO_MUTEX.unlock();
    }
}

int main() {
    Parser parser_;
    Bitboard bitBoard;
    readInput(&parser_, &bitBoard);
    return 0;
}