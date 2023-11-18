#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <vector>

#pragma once

#include "../../bitboard/includes/bitboard.hpp"

struct node
{
    double score;
    int i;
    int i_vector;
};

class MinMax {
    public:
        MinMax(Bitboard *bitboard);
        ~MinMax();
        node findBestMove(int depth, int nodeIndex, bool isMax, int maxDepth);
        void getScoreInMap();

        double updateScore(int index);
        std::pair<int,int> playTurn();
        double recurseScore(double score_, int depth, double alpha, double beta, std::pair<int, int> position, std::pair<int, int> direction);
        int getMaxDepth(int size);
        std::pair<int, int> nodeToPosition(node my_node);
    private:
        Bitboard *_bitboard;
        std::vector<node> _scores;
};