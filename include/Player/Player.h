#pragma once
#include "set"
#include "Pad.h"

class Player{
public:
    Player(std::shared_ptr<Pad> initial_pad);
    virtual Colors play(Colors color, Colors *lastChoosed) = 0;
protected:
    std::set<std::shared_ptr<Pad>> m_pads;
    void drawNeighbors(Colors color);
    Colors m_color;
private:
};
