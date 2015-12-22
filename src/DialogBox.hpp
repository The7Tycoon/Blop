#ifndef H_DIALOGBOX
#define H_DIALOGBOX

#include <string>
#include <sstream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "MainWindow.hpp"
#include "utils.hpp"

class DialogBox
{
public:
    DialogBox();
    DialogBox(const std::string &title, const std::string &text, const sf::Font &font, const sf::IntRect &rect);

    void addText(const std::string &text);

    void setText(std::vector<std::string> vText);
    void setTitle(const std::string &title);
    void setTexture(const sf::Texture &texture);
    void setFont(const sf::Font &font);
    void setRect(const sf::IntRect &rect);

    void display(MainWindow &window, sf::Time &delay);

private:
    void setRectProperties();
    void setTextProperties();
    void setSpriteProperties();
    void parse();
    void addTextToRender(MainWindow &window);
    void removeTextFromRender(MainWindow &window);

    sf::IntRect     m_rect;
    std::string     m_text, m_title, m_tmpText;
    std::vector<std::string> m_vText;
    sf::Sprite      m_sprite;
    sf::Font        m_font;
    sf::RectangleShape m_rectShape, m_borderShape; // m_borderShape actually not used for now

    sf::Text m_titleText;
    std::vector<sf::Text> m_words;

    unsigned int m_i;
    bool m_end;

};


#endif // H_DIALOGBOX
