#include "TilesetViewer.hpp"


TilesetViewer::TilesetViewer()
{

}

void TilesetViewer::loadTileset(const std::string &path, sf::Vector2u tileDim, sf::Vector2u coord, sf::Vector2u viewDim)
{
    m_viewOffset = sf::Vector2i(0, 0);

    m_tileset.loadFromFile(path);
    m_tilesetSprite.setTexture(m_tileset);
    m_tileDim = tileDim;
    m_viewDim = viewDim;

    m_coord = coord;
    m_selectedTile = sf::Vector2u(0, 0);

    m_oldMousePosition = sf::Vector2i(0, 0);

    sf::Vector2f tmp;
    tmp.x = (float) m_tileDim.x;
    tmp.y = (float) m_tileDim.y;
    m_selectedTileRect.setSize(tmp);
    m_selectedTileRect.setFillColor(sf::Color::Transparent);
    m_selectedTileRect.setOutlineColor(sf::Color::Red);
    m_selectedTileRect.setOutlineThickness(3);
    m_selectedTileRect.setPosition(m_coord.x, m_coord.y);

    sf::Vector2f vd;
    vd.x = (float) viewDim.x;
    vd.y = (float) viewDim.y;
    m_whiteBG.setSize(vd);
    m_whiteBG.setFillColor(sf::Color::White);
    m_whiteBG.setPosition(coord.x, coord.y);

    tmp.x = (float) m_coord.x;
    tmp.y = (float) m_coord.y;
    m_tilesetSprite.setPosition(tmp);

    selectTile(sf::Vector2i(m_coord.x,  m_coord.y));
    updateRectPosition();
}


/// Input : a pixel coordinate !
void TilesetViewer::selectTile(sf::Vector2i coord)
{
    m_selectedTile.x = (coord.x - m_coord.x + m_viewOffset.x) / m_tileDim.x;
    m_selectedTile.y = (coord.y - m_coord.y + m_viewOffset.y) / m_tileDim.y;

    updateRectPosition();
}

 const sf::Vector2u& TilesetViewer::getSelectedTile()
 {
     return m_selectedTile;
 }


void TilesetViewer::updateRectPosition()
{
    m_selectedTileRect.setPosition(m_selectedTile.x * m_tileDim.x + m_coord.x - m_viewOffset.x, m_selectedTile.y * m_tileDim.y + m_coord.y - m_viewOffset.y);
}

void TilesetViewer::dragTileset()
{
    sf::Vector2i position = sf::Mouse::getPosition();

    int deltaX = position.x - m_oldMousePosition.x;
    int deltaY = position.y - m_oldMousePosition.y;

    if(deltaX > -DRAG_PRECISION && deltaX < DRAG_PRECISION && deltaY > -DRAG_PRECISION && deltaY < DRAG_PRECISION)
    {
        if(m_viewOffset.x - deltaX >= 0)
        {
            m_viewOffset.x -= deltaX;
        }
        if(m_viewOffset.y - deltaY >= 0)
        {
            m_viewOffset.y -= deltaY;
        }

        /// Prevents the tileset view from going out of bounds
        if(m_viewOffset.x > m_tileset.getSize().x - m_viewDim.x)
        {
            m_viewOffset.x = m_tileset.getSize().x - m_viewDim.x;
        }

        if(m_viewOffset.y > m_tileset.getSize().y - m_viewDim.y)
        {
            m_viewOffset.y = m_tileset.getSize().y - m_viewDim.y;
        }

        if(m_viewOffset.x <= 0)
        {
            m_viewOffset.x = 0;
        }
        if(m_viewOffset.y <= 0)
        {
            m_viewOffset.y = 0;
        }
        ///

        m_tilesetSprite.setTextureRect(sf::IntRect(m_viewOffset.x, m_viewOffset.y, m_viewDim.x, m_viewDim.y));
    }

    m_oldMousePosition = position;
    updateRectPosition();

}


