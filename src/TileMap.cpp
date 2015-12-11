#include "TileMap.hpp"

TileMap::TileMap() : m_width(16), m_height(16)
{

}


bool TileMap::load(sf::Texture tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height)
{
         // load the tileset texture
        m_tileset = tileset;
        m_width = width;
        m_height = height;
        m_tileSize = tileSize;

        // resize the vertex array to fit the level size
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(width * height * 4);

        // populate the vertex array, with one quad per tile
        for (unsigned int i = 0; i < width; ++i)
            for (unsigned int j = 0; j < height; ++j)
            {
                // get the current tile number
                int tileNumber = tiles[i + j * width];

                // find its position in the tileset texture
                int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
                int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

                // get a pointer to the current tile's quad
                sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

                // define its 4 corners
                quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
                quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
                quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
                quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

                if(tileNumber != 0)
                {
                    quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
                    quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                    quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
                    quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
                }

            }

        return true;
}

void TileMap::setTile(sf::Vector2u coord, sf::Vector2u tilesetCoord)
{
    if(coord.x < 0 || coord.x >= m_width || coord.y < 0 || coord.y >= m_height)
        //throw 1;
        return;

    sf::Vertex* quad = &m_vertices[(coord.x + coord.y * m_width) * 4];

    quad[0].texCoords = sf::Vector2f(tilesetCoord.x * m_tileSize.x, tilesetCoord.y * m_tileSize.y);
    quad[1].texCoords = sf::Vector2f((tilesetCoord.x + 1) * m_tileSize.x, tilesetCoord.y * m_tileSize.y);
    quad[2].texCoords = sf::Vector2f((tilesetCoord.x + 1) * m_tileSize.x, (tilesetCoord.y + 1) * m_tileSize.y);
    quad[3].texCoords = sf::Vector2f(tilesetCoord.x * m_tileSize.x, (tilesetCoord.y + 1) * m_tileSize.y);
}

std::vector<int> TileMap::getTileArray()
{
    std::vector<int> res(m_width * m_height);
    for (unsigned int j = 0; j < m_height; ++j)
        for (unsigned int i = 0; i < m_width; ++i)
        {
            int x, y, r;

            sf::Vertex* quad = &m_vertices[(i + j * m_width) * 4];
            x = quad[0].texCoords.x / m_tileSize.x;
            y = quad[0].texCoords.y / m_tileSize.y;

            r = x + (y * (m_tileset.getSize().x / m_tileSize.x));
            res[i + j * m_width] = r;
        }
    return res;
}
