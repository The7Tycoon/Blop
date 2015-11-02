/// //////////////////////////////////// ///
///                BLOP                  ///
///           Corentin Mimeau            ///
///                 2015                 ///
/// //////////////////////////////////// ///

#include <iostream>

#include <SFML/Graphics.hpp>

#include "utils.hpp"
#include "MainWindow.hpp"
#include "Menu.hpp"
#include "Editor.hpp"

int main()
{
    sf::VideoMode desktopMode= sf::VideoMode::getDesktopMode();
    //MainWindow window(desktopMode, "Blop"/*, sf::Style::Fullscreen*/);
    MainWindow window(sf::VideoMode(1600, 900, 32), "Blop");
    window.setFramerateLimit(60);

    window.linkEvent(sf::Event::Closed,             [&window](sf::Event e){ window.close()               ; });
    window.linkEvent(sf::Event::KeyPressed,         [&window](sf::Event e){ window.executeKey(e.key.code); });
    window.linkEvent(sf::Event::MouseButtonPressed, [&window](sf::Event e){ window.executeArea(window)   ; });

    window.linkKey(sf::Keyboard::Escape, [&window](){ window.close(); });
    window.linkKey(sf::Keyboard::C,      [&window](){ window.clearRenderList(); window.clearArea(); });
    window.linkKey(sf::Keyboard::K,      [&window, &desktopMode](){
                                                                        window.close();
                                                                        if(!window.isFullscreen())
                                                                        {
                                                                            window.create(desktopMode, "Blop", sf::Style::Fullscreen);
                                                                        }
                                                                        else
                                                                        {
                                                                            window.create(desktopMode, "Blop");
                                                                        }
                                                                    });


    Coord menuCoord; menuCoord.x = 20; menuCoord.y = 500;
    Coord menuTitleCoord; menuTitleCoord.x = 20; menuTitleCoord.y = 50;
    sf::Font titleFont;
    titleFont.loadFromFile("font/Pamela.ttf");

    Menu mainMenu;
    mainMenu.setFont("font/Pamela.ttf");
    mainMenu.setTitle("Blop", 150, titleFont, menuTitleCoord);
    mainMenu.setPosition(menuCoord);
    mainMenu.addItem("Play");
    mainMenu.addItem("Editor");
    mainMenu.addItem("Options");
    mainMenu.addItem("Quit");

    Editor editor;

    //Map map0;
    //map0.loadFromeFolder("map/map0");

    window.linkArea(mainMenu.getItemBounds("Play"),    [](){std::cout << "Play\n"; });
    window.linkArea(mainMenu.getItemBounds("Editor"),  [&window, &editor](){std::cout << "Editor\n";

                                                                        //editor.open(window, "tileset/tileset.png", 32, 32, map0);
                                                                        editor.open(window, "tileset/tileset.png", 32, 32, Map::getEmptyMap(sf::Vector2u(100, 100)));
                                                                        });

    window.linkArea(mainMenu.getItemBounds("Options"), [](){std::cout << "Options\n";});
    window.linkArea(mainMenu.getItemBounds("Quit"), [&window](){window.close();});


    sf::Texture bgTexture; bgTexture.loadFromFile("img/bg.jpg");
    sf::Sprite bgSpr(bgTexture);
    window.addToRender(&bgSpr);

    window.addToRender(&mainMenu);

    while (window.isOpen())
    {
        window.processEvents();
        window.render();
    }

    return 0;
}

