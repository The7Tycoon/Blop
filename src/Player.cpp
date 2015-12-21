#include "Player.hpp"


Player::Player() : m_isWalking(false), m_speed(200), m_hDir(0), m_vDir(0)
{

}

void Player::setSprite(sf::Sprite sprite)
{
    m_sprite = sprite;
}

void Player::setWalkingCP(CoordPair left, CoordPair right)
{
    m_walkingLeft_cp = left;
    m_currentSprite = left.a;
    m_walkingRight_cp = right;

    m_sprite.setTextureRect(sf::IntRect(m_currentSprite.x, m_currentSprite.y, m_sprLength, m_sprHeight));
}

void Player::setSpriteInfo(float length, float height)
{
    m_sprHeight = height;
    m_sprLength = length;

    m_sprite.setTextureRect(sf::IntRect(0, 0, length, height));
}

void Player::spriteShift()
{
    m_currentSprite.x = (m_currentSprite.x + 1) % (m_walkingLeft_cp.b.x - m_walkingLeft_cp.a.x);
    m_sprite.setTextureRect(sf::IntRect(m_currentSprite.x*m_sprLength, m_currentSprite.y*m_sprHeight, m_sprLength, m_sprHeight));
}

void Player::update(sf::Time time)
{
    if(m_isWalking)
    {
        sf::Time elapsed = time - m_lastTime;
        sf::Vector2f p = m_sprite.getPosition();
        p.x += m_hDir * m_speed * elapsed.asSeconds();
        setPosition(p);
        m_sprite.setPosition(p);

        if(time.asMilliseconds() - m_lastSpriteTime.asMilliseconds() > 80)
        {
            spriteShift();
            m_lastSpriteTime = time;
        }
        //std::cout << p.x << ":" << p.y << "\n";
    }
    m_lastTime = time;
}

void Player::setWalking(bool w)
{
    m_isWalking = w;
}

bool Player::getWaling()
{
    return m_isWalking;
}

void Player::setDirection(int h, int v)
{
    setHDirection(h);
    setVDirection(v);

}

void Player::setHDirection(int h)
{
    if(h < 0)
    {
        if(m_hDir != -1)
           m_currentSprite = m_walkingLeft_cp.a;
        m_hDir = -1;
    }
    else if(h > 0)
    {
        if(m_hDir != 1)
            m_currentSprite = m_walkingRight_cp.a;
        m_hDir = 1;
    }
    else
    {
        m_hDir = 0;
    }
}

void Player::setVDirection(int v)
{
    if(v < 0)
    {
        m_vDir = -1;
    }
    else if(v > 0)
    {
        m_vDir = 1;
    }
    else
    {
        m_vDir = 0;
    }
}
