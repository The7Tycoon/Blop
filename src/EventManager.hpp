#ifndef H_EVENTMANAGER
#define H_EVENTMANAGER

#include <map>
#include <unordered_map>
#include <functional>
#include <iostream>
#include <SFML/Graphics.hpp>

namespace std
{
    template <>
    struct hash<sf::Rect<float> >
    {
        std::size_t operator()(const sf::Rect<float>& k) const
        {
            using std::size_t;
            using std::hash;

            return  ((hash<float>()(k.left)
                  ^ ((hash<float>()(k.top)    << 1)) >> 1)
                  ^ ((hash<float>()(k.width)  << 1)) >> 1)
                  ^  (hash<float>()(k.height) << 1);

        }
    };
}


struct FloatRectHasher;

class EventManager
{
public:
    EventManager();

    void processEvents(sf::RenderWindow *window);

    void linkEvent(sf::Event::EventType event, std::function<void(sf::Event)> f);
    void linkKey(sf::Keyboard::Key key, std::function<void()> f);
    void linkMouse(sf::Mouse::Button button, std::function<void()> f);
    void linkArea(sf::FloatRect rect, std::function<void()> f);

    void executeEvent(sf::Event::EventType e);
    void executeKey(sf::Keyboard::Key key);
    void executeArea(const sf::Window &parent);

    void clearEvents();
    void clearKeys();
    void clearArea();
    void clearMouse();


private:
     std::map<sf::Event::EventType, std::function<void(sf::Event)> > m_eventMapping;
     std::map<sf::Keyboard::Key, std::function<void()> > m_keyMapping;
     std::map<sf::Mouse::Button, std::function<void()> > m_mouseMapping;
     std::unordered_map<sf::FloatRect, std::function<void()> > m_areaMapping;

};





#endif // H_EVENTMANAGER
