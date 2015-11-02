#include "Entity.hpp"

Entity::Entity()
{

}

Entity::Entity(const std::string &name, const std::string &type, sf::Vector2f pos)
{
    create(name, type, pos);
}

void Entity::create(const std::string &name, const std::string &type, sf::Vector2f pos)
{
    m_name = name;
    m_type = type;
    m_position = pos;
}

sf::Vector2f Entity::getPosition()
{
    return m_position;
}
