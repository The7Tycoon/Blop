#ifndef H_MAPVIEWER
#define H_MAPVIEWER

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Map.hpp"

class MapViewer : public sf::Drawable, public sf::Transformable
{
public:
    MapViewer();
    MapViewer(const Map *map);

    void setMap(const Map *map);

    void setRenderedLayer(bool l1, bool l2, bool l3);
    void renderSolidMap(bool b);

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
       states.transform *= getTransform();
       /*
       target.draw(m_layer0, states);
       target.draw(m_layer1, states);
       target.draw(m_layer2, states);
        */
    }

    sf::Vector2u m_viewOffset;

    bool m_drawSolidMap;
    bool m_drawLayer0, m_drawLayer1, m_drawLayer2;

    const Map *m_map;
};


#endif // H_MAPVIEWER
