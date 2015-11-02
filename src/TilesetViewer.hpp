#ifndef H_TILESETVIEWER
#define H_TILESETVIEWER

#include <SFML/Graphics.hpp>
#include "MainWindow.hpp"


#define DRAG_PRECISION 40

class TilesetViewer : public sf::Drawable
{
public:
    TilesetViewer();

    void loadTileset(const std::string &path, sf::Vector2u tileDim, sf::Vector2u coord, sf::Vector2u viewDim);
    const sf::Vector2u& getSelectedTile();

    void linkEvent(MainWindow &window);
    void selectTile(sf::Vector2i coord);

    void updateRectPosition();
    void dragTileset();

private:


    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(m_whiteBG, states);
        target.draw(m_tilesetSprite, states);
        target.draw(m_selectedTileRect, states);
    }

    sf::Texture        m_tileset;
    sf::Sprite         m_tilesetSprite;
    sf::Vector2u       m_selectedTile, m_tileDim, m_coord, m_viewDim;
    sf::RectangleShape m_selectedTileRect, m_whiteBG;

    sf::Vector2i m_viewOffset, m_oldMousePosition;
};


#endif // H_TILESETVIEWER

