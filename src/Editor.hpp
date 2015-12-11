#ifndef H_EDITOR
#define H_EDITOR

#include <iostream>
#include <SFML/Graphics.hpp>

#include "MainWindow.hpp"
#include "Map.hpp"
#include "MapViewer.hpp"
#include "Toolbar.hpp"
#include "TilesetViewer.hpp"


/// TILESET'S COORD RELATIVE TO WINDOW'S SIZE ///
#define TS_VIEW_RATIO_X 0.7
#define TS_VIEW_RATIO_Y 0.0
/// ///////////////////////////////////////// ///


/// Class: Editor
///
/// Role : Create and manage elements related to the creation of a map
///        This includes creating and managing : - A TilesetViewer
///                                              - A Map (not created, only managed)
///                                              - A toolbar
///
/// Need :  - A MainWindow
///         - At least one tileset (path to png picture)
///         - Info about tileset (width and height of a tile)
///         - An existing map (can use the default map)
///

class Editor
{
public:
    Editor();

    void open(MainWindow &window, const std::string &tilesetPath, unsigned int tileW, unsigned int tileH, Map m);

    void openTileset(MainWindow &window, const std::string &path, unsigned int tileW, unsigned int tileH);
    void openMap(MainWindow &window, Map m);
    void createToolbar(MainWindow &window);

private:
    void linkEvent(MainWindow &window);
    void updateTextLayer();
    void saveMap_prompt();
    void openMap_prompt();

    void eraseTile_auto(MainWindow &window);
    void dragTileset_auto(MainWindow &window);
    void setTile_auto(MainWindow &window);



    sf::Texture t1, t2, t3, t4, t5, t6, t7, t8; // Toolbar's textures
    Toolbar m_toolbar;

    Map m_map;
    sf::Vector2f m_mapCoord;
    //MapViewer m_mapViewer;

    sf::Texture m_tileset;
    unsigned int m_tileW, m_tileH;
    TilesetViewer m_tilesetViewer;
    sf::Vector2u m_tilesetViewerCoord;

    int m_selectedLayer;

    sf::RectangleShape m_bottomRect;
    sf::Font m_font;
    sf::Text m_textLayer, m_textMapInfo;

};

#endif // H_EDITOR
