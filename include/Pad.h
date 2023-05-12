#pragma once
#include "Consts.h"
#include "math.h"
#include "iostream"
#include "set"
#include "queue"
#include "Shapes.h"
#include "Mosaic.h"

class Pad : public Shapes{
public:
    Pad(int id,Colors color, sf::Vector2f pos,bool is_free = true);
    virtual void draw(sf::RenderWindow &window);

private:
};
