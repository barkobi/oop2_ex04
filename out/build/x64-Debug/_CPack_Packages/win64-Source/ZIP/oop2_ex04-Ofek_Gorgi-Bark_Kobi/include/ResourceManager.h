#pragma once

#include <SFML/Graphics.hpp>

class ResourceManager{
public:
    static ResourceManager &instance();

    // functions
    sf::Font &getFont();
    sf::Texture& getText();
private:
    ResourceManager();
    sf::Font m_font;
    sf::Texture m_texture;
};