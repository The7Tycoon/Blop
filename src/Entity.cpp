#include "Entity.hpp"

Entity::Entity()
{

}

Entity::Entity(const std::string &name)
{
    create(name);
}

void Entity::create(const std::string &name)
{
    m_name = name;
}

std::string Entity::getsProperty(const std::string &pName)
{
    return m_sProperties[pName];
}

long Entity::getiProperty(const std::string &pName)
{
    return m_iProperties[pName];
}

float Entity::getfProperty(const std::string &pName)
{
    return m_fProperties[pName];
}

bool Entity::getbProperty(const std::string &pName)
{
    return m_bProperties[pName];
}

void Entity::setSProperty(const std::string &pName, const std::string &value)
{
    m_sProperties[pName] = value;
}

void Entity::setfProperty(const std::string &pName, float value)
{
    m_fProperties[pName] = value;
}

void Entity::setiProperty(const std::string &pName, long value)
{
    m_iProperties[pName] = value;
}

void Entity::setbProperty(const std::string &pName, bool value)
{
    m_bProperties[pName] = value;
}

