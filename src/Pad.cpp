#include "Pad.h"

Pad::Pad(const sf::Color color, sf::Vector2f pos,bool is_free)
    : m_shape(sf::CircleShape(PAD_WIDTH * (sqrt(3.f)/2),6)),m_isFree(is_free){
    m_shape.setFillColor(color);
    m_shape.setPosition(pos);
    m_shape.setOutlineColor(sf::Color::White);
    m_shape.setOutlineThickness(.5);
}

void Pad::uniteToGroup(const sf::Color color) {m_isFree = false; m_shape.setFillColor(color);}

void Pad::draw(sf::RenderWindow &window) {window.draw(m_shape);}