#include "Pad.h"

Pad::Pad(int id, Colors color, sf::Vector2f pos, bool is_free)
        : Shapes(id,color,pos,is_free,sf::CircleShape(PAD_WIDTH * (sqrt(3.f) / 2), 6)) {
    m_shape.setFillColor(colors_arr[color]);
    m_shape.setPosition(pos);
    m_shape.setOutlineColor(sf::Color::White);
    m_shape.setOutlineThickness(.5);
}

void Pad::draw(sf::RenderWindow &window) { window.draw(m_shape); }
