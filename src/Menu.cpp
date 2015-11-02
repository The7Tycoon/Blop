#include "menu.hpp"

Menu::Menu() : m_fontSize(80)
{
    m_font.loadFromFile("font/Pamela.ttf");
}

Menu::Menu(std::vector<std::string> strings)
{
    m_menuItem.clear();

    for(uint i = 0; i < strings.size(); ++i)
    {
        sf::Text text(strings[i], m_font);
        text.setCharacterSize(m_fontSize);
        text.setPosition(m_coord.x, i * m_fontSize + m_coord.y);
        m_menuItem.push_back(text);
    }
}

void Menu::addItem(const std::string &item)
{
    sf::Text text(item, m_font);
    text.setCharacterSize(m_fontSize);
    text.setPosition(m_coord.x, m_menuItem.size() * m_fontSize + m_coord.y);
    m_menuItem.push_back(text);

}

sf::FloatRect Menu::getItemBounds(const std::string &item) const
{
    sf::FloatRect res;

    for(uint i = 0; i < m_menuItem.size(); ++i)
    {
        if(m_menuItem[i].getString() == item)
        {
            res = m_menuItem[i].getGlobalBounds();
        }
    }

    return res;
}

void Menu::setPosition(const Coord &c)
{
    m_coord.x = c.x;
    m_coord.y = c.y;
}

void Menu::setFont(sf::Font f)
{
    m_font = f;
}

void Menu::setFont(std::string file)
{
    m_font.loadFromFile(file);
}

void Menu::setTitle(std::string label, uint size, sf::Font font, Coord pos)
{
    m_fontSizeTitle = size;
    m_fontTitle = font;

    sf::Text t(label, m_fontTitle);
    t.setCharacterSize(size);

    m_coordTitle = pos;

    m_title = t;
    m_title.setPosition(m_coordTitle.x, m_coordTitle.y);
}

Menu::~Menu()
{

}

