#ifndef H_MENU
#define H_MENU

#include <string>
#include <SFML/Graphics.hpp>

#include "utils.hpp"

class Menu : public sf::Drawable
{
public:
    Menu();
    Menu(std::vector<std::string> strings);
    ~Menu();

    void addItem(const std::string &item);

    sf::FloatRect getItemBounds(const std::string &item) const;

    void setPosition(const Coord &c);
    void setFont(sf::Font f);
    void setFont(std::string file);
    void setTitle(std::string label, uint size, sf::Font font, Coord pos);

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(m_title, states);

        for(uint i = 0; i < m_menuItem.size(); ++i)
        {
            target.draw(m_menuItem[i], states);
        }


    }

    std::vector<sf::Text> m_menuItem;
    sf::Text m_title;
    Coord m_coord, m_coordTitle;
    sf::Font m_font, m_fontTitle;
    uint m_fontSize, m_fontSizeTitle;


};
#endif // H_MENU


