#pragma once
#include "SFML/Graphics.hpp"
#include "Board.h"
#include "ColorBtn.h"

class Controller {
public:
    Controller();
    void run();
private:
    void printWindowObjects();
    void createColorBtns();
    void playerTurn();
    void setLastColors(Colors color);

    sf::RenderWindow m_window;
    Board m_board;
    ColorBtn m_colorBtns[NUM_OF_COLORS];
    Colors m_lastChoosed[2];
};
