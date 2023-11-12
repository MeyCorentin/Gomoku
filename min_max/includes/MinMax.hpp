#include <iostream>
#include <vector>

#pragma once

struct node
{
    int score;
    int i_vector;
    int i;
};

class MinMax {
    public:
        MinMax();
        ~MinMax();
        node findBestMove(int depth, int nodeIndex, bool isMax, std::vector<node> scores, int maxDepth);
        int getMaxDepth(int size);
    private:
};