#ifndef H_ENTITY
#define H_ENTITY

#include <SFML/Graphics.hpp>
#include <string>


class Entity
{
public:
    Entity();
    Entity(const std::string &name, const std::string &type, sf::Vector2f pos);
    void create(const std::string &name, const std::string &type, sf::Vector2f pos);

    sf::Vector2f getPosition();

private:
    sf::Vector2f m_position;
    std::string m_type, m_name;

};


#endif // H_ENTITY
