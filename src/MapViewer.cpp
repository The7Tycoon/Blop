#include "MapViewer.hpp"


MapViewer::MapViewer()
{
    m_map = nullptr;
}

MapViewer::MapViewer(const Map *map)
{
    setMap(map);
}

void MapViewer::setMap(const Map *map)
{
    m_map = map;
}
