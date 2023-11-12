#include <iostream>
#include <vector>

#pragma once

#include "../../bitboard/includes/bitboard.hpp"

struct node
{
    int score;
    int i_vector;
    int i;
};

class MinMax {
    public:
        MinMax(Bitboard *bitboard);
        ~MinMax();
        node findBestMove(int depth, int nodeIndex, bool isMax, std::vector<node> scores, int maxDepth);
        std::vector<node> getScoreInMap();
        void playTurn();
        int getMaxDepth(int size);
        std::pair<int, int> nodeToPosition(node my_node);
    private:
        Bitboard *_bitboard;
};