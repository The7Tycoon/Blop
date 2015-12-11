#ifndef H_UTILS
#define H_UTILS

#include <SFML/Graphics.hpp>

typedef unsigned int uint;

#define TILE_SIZE 16

enum Game_State { IN_GAME, IN_MAIN_MENU, IN_EDITOR};

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


}



#endif // H_UTILS
