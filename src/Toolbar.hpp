#ifndef H_TOOLBAR
#define H_TOOLBAR


#include <SFML/Graphics.hpp>
#include <functional>

#include "MainWindow.hpp"

class Toolbar : public sf::Drawable
{
public:
    Toolbar(sf::Vector2u position, unsigned int width, bool horizontal = false);

    void addItem(MainWindow &window, const sf::Texture &t, std::function<void()> f);



private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        for(unsigned int i = 0; i < m_sprite.size(); ++i)
        {
            target.draw(m_sprite[i], states);
        }
    }

    unsigned int m_width, n;
    sf::Vector2u m_position;
    bool m_horizontal;
    std::vector<sf::Sprite> m_sprite;

};

#endif // H_TOOLBAR
