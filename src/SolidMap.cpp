#include "SolidMap.hpp"


SolidMap::SolidMap() : m_width(0), m_height(0)
{
    m_tileSize.x = TILE_SIZE, m_tileSize.y = TILE_SIZE;
    m_solidTileShape.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
    m_solidTileShape.setFillColor(sf::Color(0, 255, 0, 128));
}

SolidMap::SolidMap(sf::Vector2f tileSize)
{
    m_tileSize = tileSize;

    m_solidTileShape.setSize(tileSize);
    m_solidTileShape.setFillColor(sf::Color(0, 255, 0, 128));
}

void SolidMap::load(std::vector<bool> tiles, unsigned int width, unsigned int height)
{
    if(tiles.size() != width * height)
        throw 2;

    m_tiles = tiles;
    m_width = width;
    m_height = height;
}

bool SolidMap::isSolid(unsigned int u, unsigned int v)
{
    if(m_tiles[u + v * m_width])
        return true;
    return false;
}

bool SolidMap::isSolid(unsigned int index)
{
    if(m_tiles[index])
        return true;
    return false;
}

void SolidMap::setSolid(unsigned int x, unsigned int y, bool b)
{
    m_tiles[x + m_width * y] = b;
}

void SolidMap::setTileSize(sf::Vector2f tileSize)
{
    m_tileSize = tileSize;
    m_solidTileShape.setSize(tileSize);
}
