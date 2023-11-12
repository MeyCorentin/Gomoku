#include <iostream>
#include <thread>

#include "min_max/src/MinMax.cpp"
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
        IO_MUTEX.unlock();
    }
}

void writeOutput(Brain *arg_brain, Bitboard *board_) {
    while (true) {
        IO_MUTEX.lock();
        arg_brain->Compute(*board_, input);
        IO_MUTEX.unlock();
    }
}

int main() {
    // MinMax algo;

    // int scores[] = {3, 5, 2, 9, 12, 5, 23, 23};
    // int size = sizeof(scores)/sizeof(scores[0]);
    // int maxDepth = algo.getMaxDepth(size);
    // int result = algo.findBestMove(0, 0, true, scores, maxDepth);

    // std::cout << "Result : " << result << std::endl;

    Parser parser_;
    Brain brain_;
    Bitboard& board_ = Bitboard::getInstance();

    std::thread t1(readInput, &parser_, &board_);
    std::thread t2(writeOutput, &brain_, &board_);

    t1.join();
    t2.join();

    return 0;
}