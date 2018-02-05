#include "TilesetMask.hpp"

TilesetMask::TilesetMask()
{

}

TilesetMask::TilesetMask(const sf::Image &im)
{
    m_mask = im;
}

TilesetMask::TilesetMask(const std::string &path)
{
    m_mask.loadFromFile(path);
}

void TilesetMask::loadMask(const sf::Image &im)
{
    m_mask = im;
}

void TilesetMask::loadMask(const std::string &path)
{
    m_mask.loadFromFile(path);
}

void TilesetMask::set(const sf::Color &color, const std::string &prop)
{
    m_properties[color] =  prop;
}

std::string TilesetMask::get(const sf::Color &color)
{
    return m_properties[color];
}

std::string TilesetMask::getPixelProp(unsigned int x, unsigned int y)
{
    sf::Color c = m_mask.getPixel(x, y);

    if(m_properties.count(c))
    {
        return m_properties[c];
    }

    std::string e = "no_prop";
    return e;
}
