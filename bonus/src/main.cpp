#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <future>

#include "../../min_max/includes/MinMax.hpp"
#include "../../parser/includes/parser.hpp"
#include "../../brain/includes/brain.hpp"
#include "../includes/Render.hpp"

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

void writeOutput(Brain *arg_brain, Bitboard *board_) {
    while (!stop_bool) {
        IO_MUTEX.lock();
        arg_brain->Compute(*board_, input);
        IO_MUTEX.unlock();
    }
}

int main() {

    Parser parser_;
    Brain brain_;
    Bitboard bitBoard;
    Render myRender(&bitBoard, &parser_);

    myRender.createBoard(20);

    std::promise<void> exitSignal;
    std::future<void> futureObj = exitSignal.get_future();
    std::thread t1(readInput, &parser_, &bitBoard);
    std::thread t2(writeOutput, &brain_, &bitBoard);

    while (!stop_bool) { //Todo fix segfault
        myRender.refreshWindow();
        myRender.checkInputs();
        myRender.updateBoard();
        myRender.drawBoard();
    }
    
    t1.join();
    t2.join();

    return 0;
}