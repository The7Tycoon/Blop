#include "Entity.hpp"

Entity::Entity()
{

}

Entity::Entity(const std::string &name)
{
    create(name);
}

void Entity::loadFromFile(const std::string &path)
{
    std::ifstream entity_f;
    entity_f.open(path.c_str());



    if(entity_f.is_open())
    {
        std::string eName;
        entity_f >> eName;
        m_name = eName;

        std::cout << "TEST\n";

        while(!entity_f.eof())
        {
            std::string name, type, value;

            std::getline(entity_f, name, ':');
            std::getline(entity_f, type, ':');
            std::getline(entity_f, value);

            std::cout << name << ", " << type << ", " << value << std::endl;

            if(type == "s")
                m_sProperties[name] = value;

            else if(type == "f")
                m_fProperties[name] = std::stof(value);

            else if(type == "i")
                m_iProperties[name] = std::stol(value);

            else if(type == "b")
            {
                bool b;
                std::istringstream s(value);
                s >> std::boolalpha >> b;
                m_bProperties[name] = b;
            }


            else
                std::cout << "Warning, discarded value in entity " << eName << ". Reason: Unknown type." << std::endl;


        }

    }
    else
        std::cout << "Error while opening entity file." << std::endl;


    entity_f.close();
}











void Entity::create(const std::string &name)
{
    m_name = name;
}

template<typename T>
T Entity::getProperty(const std::string &pName)
{

}

template<>
long Entity::getProperty(const std::string &pName)
{
    return m_iProperties[pName];
}

template<>
float Entity::getProperty(const std::string &pName)
{
    return m_fProperties[pName];
}

template<>
bool Entity::getProperty(const std::string &pName)
{
    return m_bProperties[pName];
}

template<>
std::string Entity::getProperty(const std::string &pName)
{
    return m_sProperties[pName];
}

template<typename T>
void Entity::setProperty(const std::string &pName, T value)
{

}

template<>
void Entity::setProperty(const std::string &pName, std::string value)
{
    m_sProperties[pName] = value;
}

template<>
void Entity::setProperty(const std::string &pName, float value)
{
    m_fProperties[pName] = value;
}

template<>
void Entity::setProperty(const std::string &pName, long value)
{
    m_iProperties[pName] = value;
}

template<>
void Entity::setProperty(const std::string &pName, bool value)
{
    m_bProperties[pName] = value;
}
