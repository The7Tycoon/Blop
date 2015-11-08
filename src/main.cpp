/// //////////////////////////////////// ///
///                BLOP                  ///
///           Corentin Mimeau            ///
///                2015                  ///
/// //////////////////////////////////// ///

#include <iostream>

#include <SFML/Graphics.hpp>

#include "utils.hpp"
#include "MainWindow.hpp"
#include "Menu.hpp"
#include "Editor.hpp"
#include "Entity.hpp"


void toggleFullscreen(MainWindow &window, sf::VideoMode vMode);

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
    window.linkKey(sf::Keyboard::K,      [&window, &desktopMode](){ toggleFullscreen(window, desktopMode); });


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

    Map map0;
    map0.loadFromeFolder("map/Interior");

    {
    Entity ent("myEntity");
    ent.setbProperty("isAlive", true);
    ent.setfProperty("pos_X", 12.5);
    ent.setiProperty("point", 128);
    ent.setSProperty("type", "score_item");

    std::cout << ent.getbProperty("isAlive")<< ", "
              << ent.getfProperty("pos_X")  << ", "
              << ent.getiProperty("point")  << ", "
              << ent.getsProperty("type")   << std::endl;
    }

    window.linkArea(mainMenu.getItemBounds("Play"),    [&](){   std::cout << "Play\n";

                                                                window.clearRenderList();
                                                                window.clearArea();

                                                                window.addToRender(&map0);

                                                                });
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



void toggleFullscreen(MainWindow &window, sf::VideoMode vMode)
{
    window.close();
    if(!window.isFullscreen())
    {
        window.create(vMode, "Blop", sf::Style::Fullscreen);
    }
    else
    {
        window.create(vMode, "Blop");
    }
}

