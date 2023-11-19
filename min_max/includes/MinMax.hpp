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
    std::pair<int, int> position;
};

class MinMax {
    public:
        MinMax(Bitboard *bitboard);
        ~MinMax();
        node findBestMove();
        void getScoreInMap();
        void displayScore();

        double updateScore(std::pair<int, int> position, bool attack);
        std::pair<int,int> playTurn();
        double recurseScore(double score_, int depth, std::pair<int, int> position, std::pair<int, int> direction, bool attack);
        int getMaxDepth(int size);
        std::pair<int, int> nodeToPosition(node my_node);
    private:
        Bitboard *_bitboard;
        std::vector<node> _scores_defense;
        std::vector<node> _scores_attack;
};