#include "MainWindow.hpp"

MainWindow::MainWindow()
{
    m_gameState = IN_MAIN_MENU; /* NOT USED */
    setFramerateLimit(60);

    m_isFullscreen = false;
}

MainWindow::MainWindow(sf::VideoMode vMode, const std::string &title, unsigned long windowStyle) : sf::RenderWindow(vMode, title, windowStyle)
{
    setFramerateLimit(60);
    m_currentMode = vMode;

    m_isFullscreen = false;
}

void MainWindow::processEvents()
{
    /// Explicit call
    EventManager::processEvents(this);
}

void MainWindow::render()
{
    clear();

    if(m_renderList.size() > 0)
    {
        for(unsigned int x = 0 ; x < m_renderList.size(); ++x)
        {
            draw(*m_renderList[x]/*, rs*/);
        }
    }

    display();
}

void MainWindow::addToRender(sf::Drawable *d)
{
    m_renderList.push_back(d);
}

void MainWindow::clearRenderList()
{
    m_renderList.clear();
}

void MainWindow::removeFromRenderList(sf::Drawable *d)
{
    std::vector<sf::Drawable*>::iterator it;

    it = std::find(m_renderList.begin(), m_renderList.end(), d);
    if(it != m_renderList.end())
    {
        m_renderList.erase(it);
    }
}


void MainWindow::create(sf::VideoMode mode, const sf::String &title, sf::Uint32 style, const sf::ContextSettings &settings)
{
    if(style == sf::Style::Fullscreen)
    {
        m_isFullscreen = true;
    }
    else
    {
        m_isFullscreen = false;
    }

    sf::RenderWindow::create(mode, title, style, settings);
}

bool MainWindow::isFullscreen()
{
    return m_isFullscreen;
}

void MainWindow::addTimedFunction(sf::Time freq, std::function<void()> f, bool execute)
{
    auto a = std::make_tuple(freq, sf::seconds(0), f);
    m_timedFunctions.push_back(a);

    if(execute)
        f();
}

void MainWindow::processTimedFunctions()
{
    for(auto &a : m_timedFunctions)
    {
        if( m_clock.getElapsedTime() - std::get<1>(a) >= std::get<0>(a))
        {
            std::get<1>(a) = m_clock.getElapsedTime();    // Update the last execution time
            std::get<2>(a)();                             // Call the linked function
        }
    }
}





