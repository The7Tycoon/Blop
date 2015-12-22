#include "DialogBox.hpp"

DialogBox::DialogBox() : m_end(false), m_i(0)
{

}

void DialogBox::addText(const std::string &text)
{
    m_vText.push_back(text);
}

void DialogBox::setText(std::vector<std::string> vText)
{
    //m_text = text;
    m_vText = vText;
}

void DialogBox::setTitle(const std::string &title)
{
    m_title = title;
    m_titleText.setFont(m_font);
    m_titleText.setString(m_title);
    m_titleText.setCharacterSize(16);
    m_titleText.setColor(sf::Color::White);
    m_titleText.setStyle(sf::Text::Bold);
}

void DialogBox::setTexture(const sf::Texture &texture)
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

void DialogBox::display(MainWindow &window, sf::Time &delay)
{

    setRectProperties();
    parse();
    setSpriteProperties();
    setTextProperties();
    window.addToRender(&m_rectShape);
    window.addToRender(&m_sprite);
    window.addToRender(&m_titleText);

    window.addTimedFunction(delay, [&]()
    {
        if(m_tmpText != m_vText[m_i])
        {
            removeTextFromRender(window);                         // First, we remove the text already on screen from the render list
            m_tmpText.push_back(m_vText[m_i][m_tmpText.size()]);  // Then, we add the next character to the temporary string
            parse();                                              // We split this string into words to display
            setTextProperties();                                  // We configure those words
            addTextToRender(window);                              // We add them to render
        }
    }, "letterTimer", true);

    window.addTimedFunction(sf::milliseconds(20), [&]()
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            if(m_tmpText != m_vText[m_i])
            {
                removeTextFromRender(window);
                m_tmpText.push_back(m_vText[m_i][m_tmpText.size()]);
                parse();
                setTextProperties();
                addTextToRender(window);
            }
        }
    }, "letterKey");

    window.linkKey(sf::Keyboard::D, [&]()
    {
        if(m_tmpText == m_vText[m_i])
        {
            ++m_i;
            m_tmpText.erase();
        }

        if(m_i == m_vText.size()) // Deactivation
        {
            m_tmpText.clear();                              // This is important. Reset the temporary string in order to be able to re-display the dialog box
            window.removeFromRenderList(&m_rectShape);      // Removing of the rectangle shape
            window.removeFromRenderList(&m_sprite);
            window.removeFromRenderList(&m_titleText);
            removeTextFromRender(window);                   // Removing of the text
            window.removeTimedFunction("letterTimer");
            window.removeTimedFunction("letterKey");
            window.linkKey(sf::Keyboard::D, [&](){ /*this->display(window, delay);*/ });    // Reseting of the key
        }

        //std::cout << m_tmpText << ":" << m_text << "::" << m_tmpText.size() << "::" << m_words.size() << "\n";
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

void DialogBox::parse()
{
    m_words.clear();
    std::vector<std::string> splitWords = split(m_tmpText, ' '); // Split is located in utils files

    for(unsigned int i = 0; i < splitWords.size(); ++i)
    {
        sf::Text t(splitWords[i], m_font);
        m_words.push_back(t);
    }
}

void DialogBox::setTextProperties()
{
    m_titleText.setPosition(m_rect.left + m_sprite.getGlobalBounds().width + 10, m_rect.top + 5);

    for(unsigned int i = 0; i < m_words.size(); ++i)
    {
        m_words[i].setCharacterSize(16);
        m_words[i].setColor(sf::Color::White);

        if(i == 0)
        {
            m_words[i].setPosition(m_rect.left + m_sprite.getGlobalBounds().width + 10 + m_titleText.getGlobalBounds().width + 8, m_rect.top + 5);
        }
        else
        {
            sf::Vector2f p = m_words[i-1].getPosition();
            sf::Vector2f new_p;

            if(p.x + m_words[i-1].getGlobalBounds().width + 10 + m_words[i].getGlobalBounds().width + 5 < m_rect.left + m_rect.width)
            {
                //std::cout << "TL: "  << m_rectShape.getPosition().x << ":" << m_rectShape.getSize().x << "::" << m_words[i].getString().toAnsiString() << "::" << p.x + m_words[i-1].getGlobalBounds().width + 10 + m_words[i].getGlobalBounds().width << "::" << m_rect.left + m_rect.top << "\n";
                new_p.x = p.x + m_words[i-1].getGlobalBounds().width + 10;
                new_p.y = p.y;
            }
            else
            {
                new_p.x = m_rect.left + m_sprite.getGlobalBounds().width + 10;
                new_p.y = p.y + m_words[i].getCharacterSize() + 0.25 * m_words[i].getCharacterSize();
            }

            m_words[i].setPosition(new_p);
        }
    }
}

void DialogBox::setSpriteProperties()
{
    m_sprite.setPosition(m_rect.left + 5, m_rect.top + (m_rect.height / 2) - (m_sprite.getGlobalBounds().height / 2));
}


void DialogBox::addTextToRender(MainWindow &window)
{
    for(unsigned int i = 0; i < m_words.size(); ++i)
    {
        //std::cout << "Adding...\n";
        window.addToRender(&m_words[i]);
    }
}

void DialogBox::removeTextFromRender(MainWindow &window)
{
    for(unsigned int i = 0; i < m_words.size(); ++i)
    {
        //std::cout << "Removing...\n";
        window.removeFromRenderList(&m_words[i]);
    }
}
