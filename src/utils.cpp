#include "utils.hpp"

bool operator==(const Coord &x, const Coord &y)
{
    if(x.x == y.x && x.y == y.y)
        return true;
    else
        return false;
}




/// Thanks to Evan Teran for those two functions ///
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}




