#include "Editor.hpp"

Editor::Editor() : m_toolbar(sf::Vector2u(0, 0), 64, false), m_tileW(0), m_tileH(0)
{
    t1.loadFromFile("img/toolbox_l0.png");
    t2.loadFromFile("img/toolbox_l1.png");
    t3.loadFromFile("img/toolbox_l2.png");
    t4.loadFromFile("img/toolbox_lsmap.png");

    t5.loadFromFile("img/toolbox_o.png");
    t6.loadFromFile("img/toolbox_s.png");
    t7.loadFromFile("img/toolbox_e.png");
    t8.loadFromFile("img/toolbox_q.png");


    //m_tilesetViewerCoord = sf::Vector2u(1500, 0);
    m_mapCoord = sf::Vector2f(64, 0);

    m_font.loadFromFile("font/arial.ttf");
    m_textLayer.setFont(m_font);
    m_textLayer.setCharacterSize(20);
    m_textLayer.setColor(sf::Color::Black);
}


void Editor::createToolbar(MainWindow &window)
{

    m_toolbar.addItem(window, t1, [&]{m_selectedLayer = 0; m_map.drawSolidMap(false); updateTextLayer();});
    m_toolbar.addItem(window, t2, [&]{m_selectedLayer = 1; m_map.drawSolidMap(false); updateTextLayer();});
    m_toolbar.addItem(window, t3, [&]{m_selectedLayer = 2; m_map.drawSolidMap(false); updateTextLayer();});
    m_toolbar.addItem(window, t4, [&]{m_selectedLayer = 3; m_map.drawSolidMap(true);  updateTextLayer();});

    //m_toolbar.addItem(window, t5, [&](){ window.removeFromRenderList(&m_map); openMap_prompt(); openMap(window, m_map); });
    m_toolbar.addItem(window, t5, [&](){ openMap_prompt(); });
    m_toolbar.addItem(window, t6, [&](){ saveMap_prompt(); });

    m_toolbar.addItem(window, t7, [](){  std::cout << "erase\n"; });
    m_toolbar.addItem(window, t8, [&window](){window.close();});



    window.addToRender(&m_toolbar);

}

void Editor::openTileset(MainWindow &window, const std::string &path, unsigned int tileW, unsigned int tileH)
{
    m_tilesetViewerCoord = sf::Vector2u(TS_VIEW_RATIO_X * window.getSize().x,
                                        TS_VIEW_RATIO_Y * window.getSize().y);

    m_tilesetViewer.loadTileset(path, sf::Vector2u(tileW, tileH), m_tilesetViewerCoord, sf::Vector2u( (1 - TS_VIEW_RATIO_X) * window.getSize().x,
                                                                                                      (1 - TS_VIEW_RATIO_Y) * window.getSize().y ));
    window.addToRender(&m_tilesetViewer);
}

void Editor::linkEvent(MainWindow &window)
{
    window.clearKeys();
    window.clearMouse();


    window.linkMouse(sf::Mouse::Left, [&](){ dragTileset_auto(window); setTile_auto(window); });

    window.linkMouse(sf::Mouse::Right, [&](){ eraseTile_auto(window); });

    window.linkEvent(sf::Event::MouseButtonPressed, [&](sf::Event e){
                            window.executeArea(window);

                            if(e.mouseButton.button == sf::Mouse::Left)
                            {
                                    sf::Vector2i mouse = sf::Mouse::getPosition(window);
                                    // Map view
                                    if(mouse.x < m_tilesetViewerCoord.x && mouse.x > m_mapCoord.x)
                                    {
                                        sf::Vector2u coord;
                                        coord.x = (mouse.x - m_mapCoord.x - m_map.getOffset().x) / m_tileW;
                                        coord.y = (mouse.y - m_mapCoord.y - m_map.getOffset().y) / m_tileH;

                                        try
                                        {
                                            if(m_selectedLayer == 3)
                                                m_map.setTileSolid(coord.x, coord.y, !m_map.isTileSolid(coord.x, coord.y));

                                        }
                                        catch(int e)
                                        {
                                            if(e == 1)
                                                std::cout << "Exception in Editor::linkEvent @m_map.setTile: map coord out of bounds.\n";
                                            else
                                                std::cout << "Unknown exception in Editor::linkEvent. Exception code: " << e << "\n";
                                        }

                                    }
                                }
    });

    window.linkKey(sf::Keyboard::Escape, [&window](){ window.close(); });
    window.linkKey(sf::Keyboard::C,      [&window](){ window.clearRenderList(); window.clearArea(); });
    //window.linkKey(sf::Keyboard::V,      [&window, this](){ window.removeFromRenderList(&m_tilesetViewer);});
    window.linkKey(sf::Keyboard::K,      [&window](){
                                                      sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
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


    window.linkKey(sf::Keyboard::Z, [&](){ m_map.addOffset(0, m_tileH); });
    window.linkKey(sf::Keyboard::Q, [&](){ m_map.addOffset(m_tileW, 0); });
    window.linkKey(sf::Keyboard::S, [&](){ m_map.addOffset(0, -m_tileH); });
    window.linkKey(sf::Keyboard::D, [&](){ m_map.addOffset(-m_tileW, 0); });

    window.linkKey(sf::Keyboard::L, [&](){ m_selectedLayer = (m_selectedLayer + 1) % 4;
                                           std::cout << "Selected Layer: " << m_selectedLayer << "\n";

                                           std::string layer = std::to_string(m_selectedLayer);
                                           sf::String ls(layer);
                                           sf::String str = "Selected layer = " + ls;
                                           m_textLayer.setString(str);


                                           });

    window.linkKey(sf::Keyboard::M, [&](){ m_map.drawSolidMap(!m_map.solidMapDrawed()); });
    window.linkKey(sf::Keyboard::R, [&](){  unsigned int x, y;
                                            std::cout << "New map size : \nAwaiting width input... ";
                                            std::cin >> x;
                                            std::cout << "\nAwaiting height input... ";
                                            std::cin >> y;
                                            std::cout << "\nNew size : " << x << "x" << y << "\nApplying...\n";

                                            m_map.resetDimensions(x, y);
                                            std::cout << "Done! \n"; });



}

void Editor::openMap(MainWindow &window, Map m)
{
    m_map = m;
    m_map.setPosition(m_mapCoord);

    m_selectedLayer = 0;

    window.addToRender(&m_map);
}


void Editor::open(MainWindow &window, const std::string &tilesetPath, unsigned int tileW, unsigned int tileH, Map m)
{
    window.clearRenderList();
    window.clearArea();

    m_tileW = tileW;
    m_tileH = tileH;

    m_bottomRect.setPosition(64, window.getSize().y - 24);
    m_bottomRect.setSize(sf::Vector2f(window.getSize().x, 24));
    m_bottomRect.setFillColor(sf::Color::White);
    window.addToRender(&m_bottomRect);

    m_textLayer.setPosition(64, window.getSize().y - 24);

    std::cout << "1\n";

    openMap(window, m);

    std::cout << "2\n";
    openTileset(window, tilesetPath, tileW, tileH);
    std::cout << "3\n";
    createToolbar(window);
    std::cout << "4\n";
    window.addToRender(&m_textLayer);
    std::cout << "5\n";
    window.addToRender(&m_textMapInfo);
    std::cout << "6\n";
    linkEvent(window);
    std::cout << "7\n";
}

void Editor::updateTextLayer()
{
    std::string layer = std::to_string(m_selectedLayer);
    sf::String ls(layer);
    sf::String str = "Selected layer = " + ls;
    m_textLayer.setString(str);
}

void Editor::openMap_prompt()
{
    std::string n;
    std::cout << "\n[OPEN] Map's name : ";
    std::cin >> n;
    std::cout << "\n[OPEN] Opening map...\n\n";
    std::string p = "map/" + n;

    try
    {
        m_map.loadFromeFolder(p);
    }
    catch(int e)
    {
        std::cout << "An exception occurred while opening the map... \n";
    }
}

void Editor::saveMap_prompt()
{
    std::string n, author;
    std::cout << "[SAVE] Map's name : ";
    std::cin >> n;
    m_map.setName(n);
    std::cout << "[SAVE] Map's author : ";
    std::cin >> author;
    m_map.setAuthor(author);
    std::cout << "[SAVE] Saving map...\n";
    std::string p = "map/" + n;
    try
    {
        m_map.saveToFolder(p);
    }
    catch(int e)
    {
        std::cout << "An exception occurred while saving the map... \n";
    }
}

void Editor::eraseTile_auto(MainWindow &window)
{
    // Map view
    sf::Vector2i mouse = sf::Mouse::getPosition(window);
    if(mouse.x < m_tilesetViewerCoord.x && mouse.x > m_mapCoord.x)
    {
        sf::Vector2u coord;
        coord.x = (mouse.x - m_mapCoord.x - m_map.getOffset().x) / m_tileW;
        coord.y = (mouse.y - m_mapCoord.y - m_map.getOffset().y) / m_tileH;

        try
        {
            if(m_selectedLayer < 3)
                m_map.setTile(m_selectedLayer, coord, sf::Vector2u(0, 0));
        }
        catch(int e)
        {
            if(e == 1)
                std::cout << "Exception in Editor::linkEvent @m_map.setTile: map coord out of bounds.\n";
            else
                std::cout << "Unknown exception in Editor::linkEvent. Exception code: " << e << "\n";
        }
    }
}

void Editor::dragTileset_auto(MainWindow &window)
{
    sf::Vector2i mouse = sf::Mouse::getPosition(window);

    // Tileset Viewer
    if(mouse.x > m_tilesetViewerCoord.x)
    {
        m_tilesetViewer.dragTileset();
        m_tilesetViewer.selectTile(mouse);
    }
}

void Editor::setTile_auto(MainWindow &window)
{

    if(!window.hasFocus())
        return;

    sf::Vector2i mouse = sf::Mouse::getPosition(window);

    // Map view
    if(mouse.x < m_tilesetViewerCoord.x && mouse.x > m_mapCoord.x)
    {
        sf::Vector2u coord;
        coord.x = (mouse.x - m_mapCoord.x - m_map.getOffset().x) / m_tileW;
        coord.y = (mouse.y - m_mapCoord.y - m_map.getOffset().y) / m_tileH;

        try
        {
            if(m_selectedLayer < 3)
                m_map.setTile(m_selectedLayer, coord, m_tilesetViewer.getSelectedTile());

        }
        catch(int e)
        {
            if(e == 1)
                std::cout << "Exception in Editor::linkEvent @m_map.setTile: map coord out of bounds.\n";
            else
                std::cout << "Unknown exception in Editor::linkEvent. Exception code: " << e << "\n";
        }

    }
}







