#include "Toolbar.hpp"

Toolbar::Toolbar(sf::Vector2u position, unsigned int width, bool horizontal)
{
    m_position = position;
    m_horizontal = horizontal;
    m_width = width;

}


void Toolbar::addItem(MainWindow &window, const sf::Texture &t, std::function<void()> f)
{

    sf::Sprite spr(t);

    if(m_horizontal)
        spr.setPosition(m_position.x + m_sprite.size() * m_width, m_position.y);
    else
        spr.setPosition(m_position.x, m_position.y + m_sprite.size() * m_width);

    m_sprite.push_back(spr);

    window.linkArea(spr.getGlobalBounds(), f);

}
