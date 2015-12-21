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

void MainWindow::addTimedFunction(sf::Time freq, std::function<void()> f, const std::string &id, bool execute)
{
    auto a = std::make_tuple(freq, m_clock.getElapsedTime(), f, id);
    m_timedFunctions.push_back(a);

    if(execute)
        f();
}

void MainWindow::removeTimedFunction(const std::string &id)
{
    std::vector<std::tuple<sf::Time, sf::Time, std::function<void()>, std::string> >::iterator it = m_timedFunctions.begin();

    size_t i = 0;

    for(auto &a : m_timedFunctions)
    {
        if(std::get<3>(a) == id)
        {
            m_timedFunctions.erase(it+i);
        }

        ++i; // Don't judge me for this.
    }
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

void MainWindow::clearTimedFunctionList()
{
    m_timedFunctions.clear();
}

void MainWindow::addDelayedFunction(sf::Time delay, std::function<void()> f)
{
    auto a = std::make_tuple(delay, m_clock.getElapsedTime(), f);
    m_delayedFunctions.push_back(a);
}

void MainWindow::processDelayedFunctions()
{
    size_t i = 0;
    std::vector<std::tuple<sf::Time, sf::Time, std::function<void()> > >::iterator it = m_delayedFunctions.begin();

    for(auto &a : m_delayedFunctions)
    {
        if(m_clock.getElapsedTime() - std::get<1>(a) >= std::get<0>(a))
        {
            std::get<2>(a)();
            m_delayedFunctions.erase(it+i);
        }
        ++i;
    }
}

void MainWindow::addFunction(const std::string &id, std::function<void()> f, bool execute)
{
    auto a = std::make_tuple(f, id);
    m_functions.push_back(a);

    if(execute)
        f();
}

void MainWindow::removeFunction(const std::string &id)
{
    std::vector<std::tuple<std::function<void()>, std::string> >::iterator it = m_functions.begin();
    size_t i = 0;

    for(auto &a : m_functions)
    {
        if(std::get<1>(a) == id)
        {
            m_functions.erase(it+i);
        }

        ++i; // Don't judge me for this.
    }

}

void MainWindow::clearFunctionsList()
{
    m_functions.clear();
}

void MainWindow::processFunctions()
{
    for(auto &a : m_functions)
    {
            std::get<0>(a)();                             // Call the linked function
    }

}

sf::Time MainWindow::getElapsedTime()
{
    return m_clock.getElapsedTime();
}


