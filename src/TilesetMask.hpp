#ifndef H_TILESETMASK
#define H_TILESETMASK

#include <SFML/Graphics.hpp>
#include <unordered_map>

#include "utils.hpp"

class TilesetMask
{
public:
    TilesetMask();
    TilesetMask(const sf::Image &im);
    TilesetMask(const std::string &path);

    void loadMask(const sf::Image &im);
    void loadMask(const std::string &path);

    void set(const sf::Color &color, const std::string &prop);
    std::string get(const sf::Color &color);

    std::string getPixelProp(unsigned int x, unsigned int y);

private:
    sf::Image m_mask;

    std::unordered_map<sf::Color, std::string> m_properties;

};


#endif // H_TILESETMAP
