#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#pragma once

#include "../../bitboard/includes/bitboard.hpp"

class Render {
    private:
        std::vector<std::vector<sf::RectangleShape>> _board;
        std::vector<sf::CircleShape> _pieces;
        sf::Event _event;
        sf::RenderWindow _window;

        int _windowSize;
        int _sizeCase;
        int _sizePiece;
        Bitboard *_bitboard;

    public:
        Render(Bitboard *board);
        ~Render();

        void createBoard(int size);
        void drawBoard();
        void loop();
        void refreshWindow();
        void closeWindow();
        void checkInputs();
        void updateBoard();
};