#ifndef H_TILEMAP
#define H_TILEMAP

#include <iostream>
#include <SFML/Graphics.hpp>

class TileMap : public sf::Drawable, public sf::Transformable
{

public:

    bool load(sf::Texture tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);

    std::vector<int> getTileArray();

    void setTile(sf::Vector2u coord, sf::Vector2u tilesetCoord);

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &m_tileset;

        // draw the vertex array
        target.draw(m_vertices, states);
    }

    unsigned int m_width, m_height;
    sf::Vector2u m_tileSize;

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;

};


#endif // H_TILEMAP
