#include "Hero.h"

Hero::Hero()
{
}

Hero::~Hero()
{
}

void Hero::init(std::string textureName, int frameCount, float animDuration, 
	sf::Vector2f position, float mass)
{
	m_position = position;
	m_mass = mass;
	m_grounded = false;

	m_frame_count = frameCount;
	m_anim_duration = animDuration;

	m_texture.loadFromFile(textureName);
	
	m_sprite_size = sf::Vector2i(92, 126);
	
	m_sprite.setTexture(m_texture);

	m_sprite.setTextureRect(sf::IntRect(0, 0, 
		m_sprite_size.x, m_sprite_size.y));
	
	m_sprite.setPosition(m_position);
	m_sprite.setOrigin(m_sprite_size.x / 2.0f, 
		m_sprite_size.y / 2.0f);
}

void Hero::update(float dt)
{
	// Animate Sprite
	{
		m_elapsed_time += dt;
		const auto animFrame = static_cast<int> ((m_elapsed_time / m_anim_duration) * m_frame_count) % m_frame_count;
		m_sprite.setTextureRect(sf::IntRect(animFrame * m_sprite_size.x, 0, 
			m_sprite_size.x, m_sprite_size.y));
	}
	m_velocity -= m_mass * m_gravity * dt;
	m_position.y -= m_velocity * dt;
	m_sprite.setPosition(m_position);

	if (m_position.y >= 768 * 0.75f)
	{
		m_position.y = 768 * 0.75f;
		m_force = 0;
		m_grounded = true;
		jumpCount = 0;
	}
}

void Hero::jump(float velocity)
{
	if (jumpCount < 2)
	{
		jumpCount++;
		m_velocity = velocity;
		m_grounded = false;
	}
}

sf::Sprite Hero::getSprite()
{
	return m_sprite;
}
