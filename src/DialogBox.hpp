#ifndef H_DIALOGBOX
#define H_DIALOGBOX

#include <string>
#include <SFML/Graphics.hpp>

#include "MainWindow.hpp"

class DialogBox
{
public:
    DialogBox();
    DialogBox(const std::string &title, const std::string &text, const sf::Font &font, const sf::IntRect &rect);

    void setText(const std::string &text);
    void setTitle(const std::string &title);
    void setSprite(const sf::Texture &texture);
    void setFont(const sf::Font &font);
    void setRect(const sf::IntRect &rect);

    void display(MainWindow &window);

private:
    void setRectProperties();

    sf::IntRect     m_rect;
    std::string     m_text, m_title;
    sf::Sprite      m_sprite;
    sf::Font        m_font;
    sf::RectangleShape m_rectShape, m_borderShape;

    bool m_end;

};


#endif // H_DIALOGBOX
