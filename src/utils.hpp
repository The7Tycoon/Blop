#ifndef H_UTILS
#define H_UTILS

#include <string>
#include <sstream>
#include <vector>
#include <SFML/Graphics.hpp>

typedef unsigned int uint;

#define TILE_SIZE 32

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
std::vector<std::string> split(const std::string &s, char delim);

enum Game_State { IN_GAME, IN_MAIN_MENU, IN_EDITOR};  // Obsolete

struct Coord { int x=0; int y=0;};
bool operator==(const Coord &x, const Coord &y);

struct CoordPair
{
    sf::Vector2i a;
    sf::Vector2i b;
};

namespace std
{
    template <>
    struct hash<Coord>
    {
        std::size_t operator()(const Coord& k) const
        {
            using std::size_t;
            using std::hash;

            return  (hash<float>()(k.x))
                  ^ (hash<float>()(k.y)  << 1);
        }
    };

    template <>
    struct hash<sf::Color>
    {
        std::size_t operator()(const sf::Color& color) const
        {
            using std::size_t;
            using std::hash;

            return  (hash<float>()(color.r))
                  ^ (hash<float>()(color.g)  << 1)
                  ^ (hash<float>()(color.b)  << 1)
                  ^ (hash<float>()(color.a)  << 1);
        }
    };
}



#endif // H_UTILS
