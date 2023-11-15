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
        node findBestMove(int depth, int nodeIndex, bool isMax, int maxDepth);
        void getScoreInMap();
        void updateScore(int countConsecutive, int openEnds);
        void playTurn();
        int getMaxDepth(int size);
        std::pair<int, int> nodeToPosition(node my_node);
    private:
        Bitboard *_bitboard;
        std::vector<node> _scores;
};