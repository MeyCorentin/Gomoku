#include "../includes/Render.hpp"

Render::Render(Bitboard *board, Parser *parser)
{
    _windowSize = 800;
    _window.create(sf::VideoMode(_windowSize, _windowSize), "Gomoku");
    _bitboard = board;
    _parser = parser;
    _sizePiece = 0;
    _boardCreated = false;
}

Render::~Render()
{

}

void Render::createBoard(int size)
{
    std::vector<std::vector<sf::RectangleShape>> temp_board;
    std::vector<std::vector<sf::CircleShape>> temp_boardCircle;

    size -= 1;

    _sizeCase = _windowSize / (size + 2);
    _sizePiece = (_windowSize / (size + 2)) / 2;
    _sizeMarge = _sizeCase / 2;

    for (int i = 0; i < size; i++) {
        std::vector<sf::RectangleShape> temp_line;
        for (int j = 0; j < size; j++) {
            sf::RectangleShape rectangle(sf::Vector2f(_sizeCase, _sizeCase));
            sf::Vector2f position = {(float)(i * (_sizeCase + 1) + _sizeMarge), (float)(j * (_sizeCase + 1) + _sizeMarge)};
            sf::Color color = {201,150,60,255};
            rectangle.setPosition(position);
            rectangle.setFillColor(color);
            rectangle.setOutlineThickness(1.f);
            rectangle.setOutlineColor(sf::Color::Black);
            temp_line.push_back(rectangle);
        }
        temp_board.push_back(temp_line);
    }
    for (int i = 0; i < size + 1; i++) {
        std::vector<sf::CircleShape> temp_lineCircle;
        for (int j = 0; j < size + 1; j++) {
            sf::CircleShape circle(_sizePiece);
            sf::Vector2f positionPiece = {(float)(i * (_sizeCase + 1)), (float)(j * (_sizeCase + 1))};
            sf::Color colorPiece = {255,0,0,0};
            circle.setPosition(positionPiece);
            circle.setFillColor(colorPiece);
            temp_lineCircle.push_back(circle);
        }
        temp_boardCircle.push_back(temp_lineCircle);
    }
    _board = temp_board;
    _boardCircle = temp_boardCircle;
    _boardCreated = true;
}

void Render::updateBoard()
{
    std::vector<sf::CircleShape> pieces;
    for (int i = 0; i < _bitboard->getRowSize(); i++) {
        for (int j = 0; j < _bitboard->getRowSize(); j++) {
            int color = _bitboard->getBit(std::make_pair(j, i));
            if (color != 0) {
                sf::CircleShape piece(_sizePiece);
                sf::Vector2f position = {(float)(((i) * (_sizeCase + 1)) - _sizePiece + _sizeMarge), (float)(((j) * (_sizeCase + 1) - _sizePiece + _sizeMarge))};
                piece.setPosition(position);
                if (color == 1)
                    piece.setFillColor(sf::Color::Black);
                else
                    piece.setFillColor(sf::Color::White);
                pieces.push_back(piece);
            }
        }
    }
    _pieces = pieces;
}

void Render::drawBoard()
{
    for (auto line = _board.begin(); line != _board.end(); line++) {
        for (auto case_board = (*line).begin(); case_board != (*line).end(); case_board++) {
            _window.draw(*case_board);
        }
    }
    for (auto line = _boardCircle.begin(); line != _boardCircle.end(); line++) {
        for (auto piece_board = (*line).begin(); piece_board != (*line).end(); piece_board++) {
            _window.draw(*piece_board);
        }
    }
    for (auto piece = _pieces.begin(); piece != _pieces.end(); piece++)
        _window.draw(*piece);
    _window.display();
}

void Render::refreshWindow()
{
    _window.clear({201,150,60,100});
}

void Render::closeWindow()
{
    _window.close();
}

bool Render::boardIsCreate()
{
    return _boardCreated;
}

int Render::square(int nb)
{
    return nb * nb;
}

void Render::checkInputs()
{
    while (_window.pollEvent(_event)) {
        if (_event.type == sf::Event::Closed)
            this->closeWindow();
        if (_boardCreated) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(_window);
            int i = 1;
            for (auto line = _boardCircle.begin(); line != _boardCircle.end(); line++, i++) {
                int j = 1;
                for (auto piece_board = (*line).begin(); piece_board != (*line).end(); piece_board++, j++) {
                    sf::Vector2f position = (*piece_board).getPosition();
                    std::pair<float, float> center = {position.x + _sizePiece, position.y + _sizePiece};
                    float distance = std::sqrt(square(mousePosition.x - center.first) + square(mousePosition.y - center.second));
                    if (distance < _sizePiece) {
                        (*piece_board).setFillColor(sf::Color({255,0,0,100}));
                        if (_event.type == sf::Event::MouseButtonReleased) {
                            if (_event.mouseButton.button == sf::Mouse::Left) {
                                std::string turn = "TURN " + std::to_string(j - 1) + "," + std::to_string(i - 1); //Todo change by a ,
                                _parser->C_turn(*_bitboard, turn);
                            }
                        }
                    } else
                        (*piece_board).setFillColor(sf::Color({255,0,0,0}));
                }
            }
        }
    }
}
