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

    void addDelayedFunction(sf::Time delay, std::function<void()> f);
    void processDelayedFunctions();

    void addFunction(const std::string &id, std::function<void()> f, bool execute = false);
    void removeFunction(const std::string &id);
    void clearFunctionsList();
    void processFunctions();

    bool isFullscreen();
    void toggleFullscreen(sf::VideoMode vMode);

    void create(sf::VideoMode mode, const sf::String &title, sf::Uint32 style=sf::Style::Default, const sf::ContextSettings &settings=sf::ContextSettings());

    sf::Time getElapsedTime();
    //void update();



private:
    Game_State m_gameState;

    bool m_isFullscreen;

    sf::VideoMode m_currentMode;
    sf::Clock m_clock;

    std::vector<sf::Drawable*> m_renderList;

    std::vector<std::tuple<sf::Time, sf::Time, std::function<void()>, std::string> > m_timedFunctions;
    std::vector<std::tuple<sf::Time, sf::Time, std::function<void()> > > m_delayedFunctions;
    std::vector<std::tuple<std::function<void()>, std::string> > m_functions;

};


#endif // H_MAINWINDOW
