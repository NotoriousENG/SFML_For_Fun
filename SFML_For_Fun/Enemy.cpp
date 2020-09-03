#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::init(std::string textureName, sf::Vector2f position, float _speed)
{
	m_speed = _speed;
	m_position = position;

	m_texture.loadFromFile(textureName);
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_position);
	m_sprite.setOrigin(m_texture.getSize().x / 2.0f, 
		m_texture.getSize().y / 2.0f);
}

void Enemy::update(float dt)
{
	m_sprite.move(m_speed * dt, 0);
}

sf::Sprite Enemy::getSprite()
{
	return m_sprite;
}
