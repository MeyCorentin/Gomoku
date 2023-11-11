#include "../includes/brain.hpp"

Brain::Brain() {

}


void Brain::Compute(std::string &arg_input)
{
    if (!arg_input.empty()) {
        std::cout << "You entered: " << arg_input << std::endl;
        arg_input.clear();
    }
}