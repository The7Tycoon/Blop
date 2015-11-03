#include "Entity.hpp"

Entity::Entity()
{

}

Entity::Entity(const std::string &name, const std::string &type)
{
    create(name, type);
}

void Entity::create(const std::string &name, const std::string &type)
{
    m_name = name;
    m_type = type;
}

std::string Entity::getProperty(const std::string &pName)
{
    return m_properties[pName];
}
