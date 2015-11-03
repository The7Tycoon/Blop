#ifndef H_ENTITY
#define H_ENTITY

#include <SFML/Graphics.hpp>
#include <string>


class Entity
{
public:
    Entity();
    Entity(const std::string &name, const std::string &type);
    void create(const std::string &name, const std::string &type);

    std::string getProperty(const std::string &pName);

private:
    std::string m_type, m_name;

    std::map<std::string, std::string> m_properties;

};


#endif // H_ENTITY
