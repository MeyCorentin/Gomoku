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
    bool operator==(const node& other) const {
        return score == other.score &&
            i == other.i &&
            position == other.position;
    }
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
        int maxPossibleLine(std::pair<int, int> position, std::pair<int,int> direction, bool attack);
        int pionNumberInDirection(std::pair<int, int> position, std::pair<int,int> direction, bool attack);
        int spaceFree(std::pair<int, int> position, std::pair<int,int> direction, bool attack);
        int getMaxDepth(int size);
        std::pair<int, int> nodeToPosition(node my_node);
        int evaluatePosition(bool attack);
        bool fourOpen(std::pair<int, int> position, std::pair<int,int> direction, bool attack);
        int evaluateCell(std::pair<int, int> position, std::pair<int,int> direction, bool attack);
        bool fourClose(std::pair<int, int> position, std::pair<int,int> direction, bool attack);
        bool threeOpen(std::pair<int, int> position, std::pair<int,int> direction, bool attack);
        bool twoOpen(std::pair<int, int> position, std::pair<int,int> direction, bool attack);
        bool threeClose(std::pair<int, int> position, std::pair<int,int> direction, bool attack);
        bool fourSplit(std::pair<int, int> position, std::pair<int,int> direction, bool attack);
        bool threeSplit(std::pair<int, int> position, std::pair<int,int> direction, bool attack);
        bool threeJump(std::pair<int, int> position, std::pair<int,int> direction, bool attack);
        bool threeTwoOne(std::pair<int, int> position, std::pair<int,int> direction, bool attack);
        bool threeBlock(std::pair<int, int> position, std::pair<int,int> direction, bool attack);
        std::pair<int, int> depthMinMax(int depth, MinMax min_max, bool attack);
        int recursiveEvaluation(int depth, MinMax min_max, bool attack);
    private:
            Bitboard *_bitboard;
            std::vector<node> _scores_defense;
            std::vector<node> _scores_attack;
};