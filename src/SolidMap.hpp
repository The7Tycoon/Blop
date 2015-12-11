#ifndef H_SOLIDMAP
#define H_SOLIDMAP

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "utils.hpp"

class SolidMap : public sf::Drawable, public sf::Transformable
{
public:
    SolidMap();
    SolidMap(sf::Vector2f tileSize);

    void load(std::vector<bool> tiles, unsigned int width, unsigned int height);
    bool isSolid(unsigned int u, unsigned int v);
    bool isSolid(unsigned int index);

    void setSolid(unsigned int x, unsigned int y, bool b);

    void setTileSize(sf::Vector2f tileSize);

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();

        for(size_t i = 0; i < m_tiles.size(); ++i)
        {
            if(m_tiles[i])
            {
                sf::Transform t;
                t.translate((i % m_width) * m_tileSize.x, i / m_width * m_tileSize.y);

                t *= states.transform;

                target.draw(m_solidTileShape, t);
            }
        }


    }

    std::vector<bool> m_tiles;
    unsigned int m_width, m_height;

    sf::Vector2f m_tileSize;
    sf::RectangleShape m_solidTileShape;

};

#endif // H_SOLIDMAP
