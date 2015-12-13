#ifndef H_MAINWINDOW
#define H_MAINWINDOW

#include <SFML/Graphics.hpp>
#include <map>
#include <functional>
#include <iostream>
#include <string>
#include <tuple>

#include "EventManager.hpp"
#include "utils.hpp"


class MainWindow : public sf::RenderWindow, public EventManager
{
public:
    MainWindow();
    MainWindow(sf::VideoMode vMode, const std::string &title, unsigned long windowStyle=(/*sf::Style::Resize|*/sf::Style::Close));

    void processEvents();

    void addToRender(sf::Drawable *d);
    void removeFromRenderList(sf::Drawable *d);
    void clearRenderList();
    void render();


    void addTimedFunction(sf::Time freq, std::function<void()> f, const std::string &id, bool execute = false);
    void removeTimedFunction(const std::string &id);
    void clearTimedFunctionList();
    void processTimedFunctions();


    bool isFullscreen();

    void create(sf::VideoMode mode, const sf::String &title, sf::Uint32 style=sf::Style::Default, const sf::ContextSettings &settings=sf::ContextSettings());

    //void update();



private:
    Game_State m_gameState;

    bool m_isFullscreen;

    sf::VideoMode m_currentMode;
    sf::Clock m_clock;

    std::vector<sf::Drawable*> m_renderList;

    std::vector<std::tuple<sf::Time, sf::Time, std::function<void()>, std::string> > m_timedFunctions;
    //std::vector<std::function<void()>> updateList;

};


#endif // H_MAINWINDOW
