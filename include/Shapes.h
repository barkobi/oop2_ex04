#pragma once

#include <Mosaic.h>

#include <utility>

class Shapes {
public:
    Shapes(int id, Colors color, sf::Vector2f pos, bool is_free, sf::CircleShape shape) : m_id(id), m_color(color),
                                                                                          m_pos(pos),
                                                                                          m_is_free(is_free),
                                                                                          m_shape(std::move(shape)) {}

    Colors getColor() { return m_color; }

    int getId() const { return m_id; }

    virtual void draw(sf::RenderWindow &window) = 0;

    void setColor(Colors color) {
        m_color = color;
        m_shape.setFillColor(sf::Color(m_color));
    }

    void setOutline(bool outlines_on) {
        if (outlines_on) {
            m_shape.setOutlineThickness(2);
        } else {
            m_shape.setOutlineThickness(.5);
        }
    }

    bool isFree() const { return m_is_free; }

    void setFree(bool is_free) { m_is_free = is_free; }


protected:
    Colors m_color;
    bool m_is_free;
    sf::CircleShape m_shape;

private:
    int m_id;
    sf::Vector2f m_pos;
};