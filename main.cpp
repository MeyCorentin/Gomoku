#include <iostream>
#include <thread>
#include <mutex>
#include "parser/src/parser.cpp"
#include "brain/src/brain.cpp"

std::mutex mtx;
std::string input;

void readInput(Parser *arg_parser) {
    while (true) {
        arg_parser->Compute(input);
        mtx.lock();
        if (input == "exit") {
            mtx.unlock();
            break;
        }
        mtx.unlock();
    }
}

void writeOutput(Brain *arg_brain) {
    while (true) {
        mtx.lock();
        arg_brain->Compute(input);
        if (input == "exit") {
            mtx.unlock();
            break;
        }
        mtx.unlock();
    }
}


int main() {
    Parser parser_;
    Brain brain_;

    std::thread t1(readInput, &parser_);
    std::thread t2(writeOutput, &brain_);

    t1.join();
    t2.join();

    return 0;
}