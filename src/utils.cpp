#include "utils.hpp"

bool operator==(const Coord &x, const Coord &y)
{
    if(x.x == y.x && x.y == y.y)
        return true;
    else
        return false;
}





