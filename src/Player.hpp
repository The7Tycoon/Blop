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

    void spriteShift();


private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(m_sprite, states);
    }


    sf::Sprite m_sprite;
    CoordPair m_walkingLeft_cp, m_walkingRight_cp;
    sf::Vector2i m_currentSprite;
    float m_sprHeight, m_sprLength;


};



#endif // H_PLAYER
