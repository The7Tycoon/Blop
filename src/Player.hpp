#ifndef H_PLAYER
#define H_PLAYER

#include "Entity.hpp"
#include "utils.hpp"

// 60l 90h 480l 450h

class Player : public Entity, public sf::Drawable, public sf::Transformable
{
public:
    Player();

    void setSprite(sf::Sprite sprite);
    void setWalkingCP(CoordPair left, CoordPair right);
    void setSpriteInfo(float length, float height);

    void setWalking(bool w);
    bool getWaling();

    void setDirection(int h, int v);
    void setHDirection(int h);
    void setVDirection(int v);

    void spriteShift();

    void update(sf::Time time);

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(m_sprite, states);
    }


    sf::Sprite      m_sprite;
    CoordPair       m_walkingLeft_cp, m_walkingRight_cp;
    sf::Vector2i    m_currentSprite;
    sf::Time        m_lastTime, m_lastSpriteTime;

    float    m_sprHeight, m_sprLength;
    float    m_speed;
    float    m_isWalking;
    int      m_hDir;
    int      m_vDir;


};



#endif // H_PLAYER
