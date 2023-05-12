

#include "Player/Player.h"

Player::Player() {}

void Player::drawNeighbors(Colors color){
    m_color = color;
    for(auto &pad : m_pads){
        auto united = pad.uniteToGroup(color);

        for(auto &tmp : united)
            m_pads.insert(tmp);
    }

}

void Player::setPad(MosaicNode<std::shared_ptr<Shapes>>* new_pad) {
    m_pads.insert(*new_pad);
    m_color = new_pad->data->getColor();
}

int Player::getNumOfPads() {
    return m_pads.size();
}