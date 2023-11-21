#include "../includes/Render.hpp"

Render::Render()
{
    _windowSize = 200;
    _window.create(sf::VideoMode(_windowSize, _windowSize), "Gomoku");
}

Render::~Render()
{

}

void Render::createBoard(int size)
{
    std::vector<std::vector<sf::RectangleShape>> temp_board;

    _sizeCase = _windowSize / size - 1;

    for (int i = 0; i < size; i++) {
        std::vector<sf::RectangleShape> temp_line;
        for (int j = 0; j < size; j++) {
            sf::RectangleShape rectangle(sf::Vector2f(_sizeCase, _sizeCase));
            sf::Vector2f position = {(float)(i * (_sizeCase + 1)), (float)(j * (_sizeCase + 1))};
            sf::Color color = {201,150,60,100};
            rectangle.setPosition(position);
            rectangle.setFillColor(color);
            temp_line.push_back(rectangle);
        }
        temp_board.push_back(temp_line);
    }
    _board = temp_board;
}

void Render::drawBoard()
{
    for (auto line = _board.begin(); line != _board.end(); line++) {
        for (auto case_board = (*line).begin(); case_board != (*line).end(); case_board++) {
            _window.draw(*case_board);
        }
    }
    _window.display();
}

void Render::refreshWindow()
{
    _window.clear();
}

void Render::closeWindow()
{
    _window.close();
}

void Render::checkInputs()
{
    while (_window.pollEvent(_event)) {
        if (_event.type == sf::Event::Closed)
            this->closeWindow();
        if (_event.type == sf::Event::MouseButtonReleased) {
            if (_event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(_window);
                std::cout << "Position : " << mousePosition.x << "," << mousePosition.y << std::endl;
            }
        }
    }
}

void Render::loop()
{
    while (_window.isOpen()) {
        this->refreshWindow();
        this->checkInputs();
        this->drawBoard();
    }
}