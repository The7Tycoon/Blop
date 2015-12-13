#include "EventManager.hpp"

EventManager::EventManager()
{

}

void EventManager::processEvents(sf::RenderWindow *window)
{
    //std::cout << "event\n";
    sf::Event event;
    while (window->pollEvent(event))
    {
        // Checks if the event has been registered in the map
        if(m_eventMapping.count(event.type))
        {
            // If so, executes the function linked to it
            m_eventMapping[event.type](event);

        }
    }


    // Processes mouse button
    for(auto i : m_mouseMapping)
    {
        if(sf::Mouse::isButtonPressed(i.first))
        {
             m_mouseMapping[i.first]();
        }
    }

}

void EventManager::linkEvent(sf::Event::EventType event, std::function<void(sf::Event)> f)
{
    m_eventMapping[event] = f;
}

void EventManager::linkKey(sf::Keyboard::Key key, std::function<void()> f)
{
    m_keyMapping[key] = f;
}

void EventManager::linkMouse(sf::Mouse::Button button, std::function<void()> f)
{
    m_mouseMapping[button] = f;
}
 void EventManager::linkArea(sf::FloatRect rect, std::function<void()> f)
{
    m_areaMapping[rect] = f;
}



void EventManager::executeKey(sf::Keyboard::Key key)
{
    try
    {
        m_keyMapping[key]();
    }
    catch(...)
    {
        std::cout << "Exception occured in EventManager::executeKey !\n"
                  << "The key you pressed has probably not been linked to any function.\n";
    }
}

void EventManager::executeArea(const sf::Window &parent)
{
    if(m_areaMapping.empty())
        return;

    sf::Vector2i pos = sf::Mouse::getPosition(parent);

    for(auto a : m_areaMapping)
    {
            if(pos.x >= a.first.left && pos.x < (a.first.left + a.first.width) && pos.y >= a.first.top && pos.y <= (a.first.top + a.first.height))
            {
                try
                {
                    //m_areaMapping[a.first]();
                    a.second();
                }
                catch(...)
                {
                    std::cout << "Exception occurred in EventManager::executeArea !\n"
                              << "The area you clicked in has probably not been linked to any valid function but has been registered.\n";
                }
            }

            if(m_areaMapping.empty())
                break;
    }
}

void EventManager::clearEvents()
{
    m_eventMapping.clear();
}

void EventManager::clearKeys()
{
    m_keyMapping.clear();
}

void EventManager::clearArea()
{
    m_areaMapping.clear();
}

void EventManager::clearMouse()
{
    m_mouseMapping.clear();
}

