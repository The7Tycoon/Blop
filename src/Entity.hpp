#ifndef H_ENTITY
#define H_ENTITY

#include <SFML/Graphics.hpp>
#include <string>


class Entity
{
public:
    Entity();
    Entity(const std::string &name);
    void create(const std::string &name);

    std::string getsProperty(const std::string &pName);
    long getiProperty(const std::string &pName);
    float getfProperty(const std::string &pName);
    bool getbProperty(const std::string &pName);

    void setSProperty(const std::string &pName, const std::string &value);
    void setfProperty(const std::string &pName, float value);
    void setiProperty(const std::string &pName, long value);
    void setbProperty(const std::string &pName, bool value);




private:
    std::string m_name;

    //std::map<std::string, std::string> m_properties;

    std::map<std::string, float> m_fProperties;
    std::map<std::string, long> m_iProperties;
    std::map<std::string, bool> m_bProperties;
    std::map<std::string, std::string> m_sProperties;



};


#endif // H_ENTITY
