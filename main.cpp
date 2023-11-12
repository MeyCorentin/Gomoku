#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

#include "min_max/includes/MinMax.hpp"
#include "parser/includes/parser.hpp"
#include "brain/includes/brain.hpp"

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

    // std::vector<node> scores = {{3, 0, 1}, {5, 0, 2}, {2, 0, 3}, {9, 0, 4}, {12, 0, 5}, {5, 0, 6}, {23, 0, 7}, {23, 0, 8}};
    // int size = scores.size();
    // int maxDepth = algo.getMaxDepth(size);
    // node result = algo.findBestMove(0, 0, true, scores, maxDepth);

    // std::cout << "Result : " << result.score << std::endl;

    Parser parser_;
    Brain brain_;
    Bitboard& board_ = Bitboard::getInstance();

    std::thread t1(readInput, &parser_, &board_);
    std::thread t2(writeOutput, &brain_, &board_);

    t1.join();
    t2.join();

    return 0;
}