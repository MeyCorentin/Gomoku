#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#pragma once


class Render {
    private:
        std::vector<std::vector<sf::RectangleShape>> _board;
        sf::Event _event;
        sf::RenderWindow _window;

        int _windowSize;
        int _sizeCase;

    public:
        Render();
        ~Render();

        void createBoard(int size);
        void drawBoard();
        void loop();
        void refreshWindow();
        void closeWindow();
        void checkInputs();
};