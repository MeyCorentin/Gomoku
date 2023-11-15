#include <iostream>

#pragma once

class MinMax {
    public:
        MinMax();
        ~MinMax();
        int findBestMove(int depth, int nodeIndex, bool isMax, int scores[], int maxDepth);
        int getMaxDepth(int size);
    private:
};