#pragma once
#include "set"
#include "Pad.h"

class Player{
public:
    Player();
    void setPad(MosaicNode<std::shared_ptr<Shapes>>* new_pad);
    virtual Colors play(Colors color, Colors *lastChoosed) = 0;
    virtual ~Player() = default;
    int getNumOfPads();
    std::set<MosaicNode<std::shared_ptr<Shapes>>> *getPads() { return &m_pads;}
protected:
    std::set<MosaicNode<std::shared_ptr<Shapes>>> m_pads;
    void drawNeighbors(Colors color);
    Colors m_color;
private:
};
