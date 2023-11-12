#include <iostream>
#include <thread>

#include <vector>
#include <mutex>
#include "parser/src/parser.cpp"
#include "brain/src/brain.cpp"
#include "bitboard/src/bitboard.cpp"

std::mutex IO_MUTEX;
std::string input;

void readInput(Parser *arg_parser, Bitboard *board_) {
    while (true) {
        IO_MUTEX.lock();
        arg_parser->Compute(*board_, input);
        if (input == "exit") {
            IO_MUTEX.unlock();
            break;
        }
        IO_MUTEX.unlock();
    }
}

void writeOutput(Brain *arg_brain, Bitboard *board_) {
    while (true) {
        IO_MUTEX.lock();
        arg_brain->Compute(*board_, input);
        if (input == "exit") {
            IO_MUTEX.unlock();
            break;
        }
        IO_MUTEX.unlock();
    }
}

int main() {
    Parser parser_;
    Brain brain_;
    Bitboard& board_ = Bitboard::getInstance();

    std::thread t1(readInput, &parser_, &board_);
    std::thread t2(writeOutput, &brain_, &board_);

    t1.join();
    t2.join();

    return 0;
}