#pragma once

#include "Mosaic.h"
#include "Pad.h"


class Board {
public:
    ~Board() = default;
    void create();
    void printBoardObject(sf::RenderWindow &window);
    MosaicNode<std::shared_ptr<Shapes>> *getBottomLeftCorner();
    MosaicNode<std::shared_ptr<Shapes>> *getTopRightCorner();
    sf::FloatRect getBoardBounds();
    void blur(sf::RenderWindow &window);
    void createNeighbors();

private:
    void initOverlay(float starting_x, float starting_y, float width, float height);
    Mosaic<MosaicNode<std::shared_ptr<Shapes>>> m_pads;
    sf::RectangleShape m_overlay[5];
};



