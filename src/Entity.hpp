#ifndef H_ENTITY
#define H_ENTITY

#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

class Entity
{
public:
    Entity();
    Entity(const std::string &name);
    void create(const std::string &name);

    void loadFromFile(const std::string &path);

    template<typename T>
    T getProperty(const std::string &pName);

    template<typename T>
    void setProperty(const std::string &pName, T value);




private:
    std::string m_name;

    //std::map<std::string, std::string> m_properties;

    std::map<std::string, float>       m_fProperties;
    std::map<std::string, long>        m_iProperties;
    std::map<std::string, bool>        m_bProperties;
    std::map<std::string, std::string> m_sProperties;



};


#endif // H_ENTITY
