#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <vector>

#pragma once

#include "../../bitboard/includes/bitboard.hpp"

struct node
{
    float score;
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
        
        int countSpaceFree();
        int updateScore(std::pair<int, int> position, bool attack);
        std::pair<int,int> playTurn();
        double recurseScore(double score_, int depth, std::pair<int, int> position, std::pair<int, int> direction, bool attack);
        int maxPossibleLine(std::pair<int, int> position, std::pair<int,int> direction, bool attack);
        int pionNumberInDirection(std::pair<int, int> position, std::pair<int,int> direction);
        int spaceFree(std::pair<int, int> position, std::pair<int,int> direction);
        int getMaxDepth(int size);
        std::pair<int, int> nodeToPosition(node my_node);
        float evaluatePosition();
        bool fourOpen(std::pair<int, int> position, std::pair<int,int> direction);
        float evaluateCell(std::pair<int, int> position, std::pair<int,int> direction);
        bool fourClose(std::pair<int, int> position, std::pair<int,int> direction);
        bool threeOpen(std::pair<int, int> position, std::pair<int,int> direction);
        bool twoOpen(std::pair<int, int> position, std::pair<int,int> direction);
        bool threeClose(std::pair<int, int> position, std::pair<int,int> direction);
        bool fourSplit(std::pair<int, int> position, std::pair<int,int> direction);
        bool threeTwoOneBlock(std::pair<int, int> position, std::pair<int,int> direction);
        bool threeJump(std::pair<int, int> position, std::pair<int,int> direction);
        bool threeTwoOne(std::pair<int, int> position, std::pair<int,int> direction);
        bool threeBlock(std::pair<int, int> position, std::pair<int,int> direction);
        std::pair<int, int> depthMinMax(int depth, MinMax min_max, bool attack);
        bool fiveEnd(std::pair<int, int> position, std::pair<int,int> direction);
        bool twoClose(std::pair<int, int> position, std::pair<int,int> direction);
        int currentLineNumber(std::pair<int, int> position, std::pair<int,int> direction);
        int endInDiretion(std::pair<int, int> position, std::pair<int,int> direction);
        bool threeOpenBig(std::pair<int, int> position, std::pair<int,int> direction);
        bool doubleThreeOpen(std::pair<int, int> position, std::pair<int,int> direction);
        bool fiveSplit(std::pair<int, int> position, std::pair<int,int> direction);
        bool is_begin = false;
    private:
            Bitboard *_bitboard;
            std::vector<node> _scores_defense;
            std::vector<node> _scores_attack;
};