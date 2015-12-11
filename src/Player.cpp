#include "Player.hpp"


Player::Player()
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
