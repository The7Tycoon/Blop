#ifndef H_MAP
#define H_MAP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <direct.h>

#include "TileMap.hpp"
#include "SolidMap.hpp"
#include "utils.hpp"

/// Class: Map
///
/// Holds a map in memory. A map is composed of multiple arrays (3 sprite arrays, 1 solidmap array, ?entity?)
/// A Map is a drawable object, it can be directly drawn on-screen
///
/// Role : - To load an existing map from drive
///        - To save a map on drive
///        - To allow easy access and modification of a tile's property
///


class Map : public sf::Drawable, public sf::Transformable
{
public:
    Map();

    void loadFromeFolder(const std::string &path);
    void saveToFolder(const std::string &path);


    void setTile(unsigned int layer, sf::Vector2u coord, sf::Vector2u tilesetCoord);
    bool isTileSolid(unsigned int x, unsigned int y);
    void setTileSolid(unsigned int x, unsigned int y, bool b);

    static Map getEmptyMap(sf::Vector2u s, const std::string &path);

    void resetDimensions(unsigned int w, unsigned int h);
    void manualLoad(const std::string &name, const std::string &author, unsigned int width, unsigned int height,
                    const std::string &t0, const std::string &t1, const std::string &t2);

    std::string getName();
    void setName(std::string name);
    void setAuthor(std::string author);

    void addOffset(int x, int y);
    sf::Vector2f getOffset();

    void drawSolidMap(bool b);
    bool solidMapDrawed();

    void setScale(sf::Vector2f s);
    void setScale(float x, float y);

    sf::Vector2f getScale();

private:
    bool loadIndex(const std::string &path);
    void loadLayer(unsigned int layerNumber, const std::string &path, int* layer);
    void loadSolidMap(const std::string &path, std::vector<bool> &solid);

    void saveLayer(const std::string &path, int layer);
    void saveSolidMap(const std::string &path);


    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        //std::cout << "Map draw\n";
        states.transform *= getTransform();

        states.transform.translate(m_viewOffset);

        target.draw(m_layer0, states);
        target.draw(m_layer1, states);
        target.draw(m_layer2, states);

        if(m_drawSolidMap)
            target.draw(m_solidMap, states);

    }

    std::string m_name, m_author, m_tileset0_path, m_tileset1_path, m_tileset2_path;
    unsigned int m_width, m_height;

    sf::Texture m_tileset0,
                m_tileset1,
                m_tileset2;

    TileMap m_layer0,
            m_layer1,
            m_layer2;

    SolidMap m_solidMap;

    sf::Vector2f m_viewOffset, m_scale;

    bool m_drawSolidMap;
};

#endif // H_MAP
