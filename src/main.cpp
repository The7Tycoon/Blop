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
#include "Player.hpp"


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



    Entity ent("myEntity");

    ent.loadFromFile("base_ent/player.ent");

    std::cout << ent.getProperty<std::string>("skin") << std::endl;

    Player p;
    p.create("Player");
    sf::Texture playerTexture; playerTexture.loadFromFile("img/wizard_1.png");
    sf::Sprite playerSprite(playerTexture);
    p.setSprite(playerSprite);
    p.setSpriteInfo(60, 90);

    CoordPair left; left.a = sf::Vector2i(0, 1); left.b = sf::Vector2i(7, 1);
    p.setWalkingCP(left, left);
    window.linkKey(sf::Keyboard::W,      [&p](){ p.spriteShift(); });


    window.linkArea(mainMenu.getItemBounds("Play"), [&window, &map0]()
    {
        std::cout << "Play\n";

        window.clearRenderList();
        window.clearArea();

        map0.loadFromeFolder("map/Cave");
        window.addToRender(&map0);

    });

    window.linkArea(mainMenu.getItemBounds("Editor"),  [&window, &editor]()
    {
        std::cout << "Editor\n";
        editor.open(window, "img/mininicular64.png", TILE_SIZE, TILE_SIZE, Map::getEmptyMap(sf::Vector2u(100, 100), "img/mininicular64.png"));

    });

    window.linkArea(mainMenu.getItemBounds("Options"), [&](){p.spriteShift(); std::cout << "Options\n";});
    window.linkArea(mainMenu.getItemBounds("Quit"), [&window](){window.close();});


    sf::Texture bgTexture; bgTexture.loadFromFile("img/bg.jpg");
    sf::Sprite bgSpr(bgTexture);
    window.addToRender(&bgSpr);

    window.addToRender(&mainMenu);
    window.addToRender(&p);

    int i = 0;
    window.addTimedFunction(sf::seconds(2), [&i](){ i++; std::cout << i << "\n";}, "i");
    window.linkKey(sf::Keyboard::X, [&window](){ window.removeTimedFunction("i"); });

    while (window.isOpen())
    {
        window.processEvents();
        window.processTimedFunctions();
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

