#ifndef H_TILEMAP
#define H_TILEMAP

#include <iostream>
#include <SFML/Graphics.hpp>

class TileMap : public sf::Drawable, public sf::Transformable
{

public:
    TileMap();

    bool load(sf::Texture tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);

    std::vector<int> getTileArray();

    void setTile(sf::Vector2u coord, sf::Vector2u tilesetCoord);

    void setScale(sf::Vector2f s);
    void setScale(float x, float y);

    sf::Vector2f getScale();

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();
        states.transform.scale(m_scale.x, m_scale.y/*, target.getSize().x / 2, target.getSize().y / 2*/);

        // apply the tileset texture
        states.texture = &m_tileset;

        // draw the vertex array
        target.draw(m_vertices, states);
    }

    unsigned int m_width, m_height;
    sf::Vector2u m_tileSize;
    sf::Vector2f m_scale;

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;

};


#endif // H_TILEMAP
