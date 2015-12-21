#include "DialogBox.hpp"

DialogBox::DialogBox() : m_end(false)
{

}


void DialogBox::setText(const std::string &text)
{
    m_text = text;
}

void DialogBox::setTitle(const std::string &title)
{
    m_title = title;
}

void DialogBox::setSprite(const sf::Texture &texture)
{
    m_sprite.setTexture(texture);
}

void DialogBox::setFont(const sf::Font &font)
{
    m_font = font;
}

void DialogBox::setRect(const sf::IntRect &rect)
{
    m_rect = rect;
}

void DialogBox::display(MainWindow &window)
{
    std::cout << "Test\n";
    setRectProperties();
    window.addToRender(&m_rectShape);

    window.linkKey(sf::Keyboard::D, [&]()
    {
        std::cout << "Test2\n";
        window.removeFromRenderList(&m_rectShape);
        window.linkKey(sf::Keyboard::D, [&](){ this->display(window);});
    });
}


void DialogBox::setRectProperties()
{
    sf::Vector2f s;
    s.x = m_rect.width;
    s.y = m_rect.height;

    sf::Vector2f p;
    p.x = m_rect.left;
    p.y = m_rect.top;

    m_rectShape.setSize(s);
    m_rectShape.setPosition(p);
    m_rectShape.setFillColor(sf::Color::Black);
    m_rectShape.setOutlineThickness(5);
    m_rectShape.setOutlineColor(sf::Color::White);
}
