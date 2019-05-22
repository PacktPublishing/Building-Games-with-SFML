#include "Character.hpp"

Character::Character()
:m_speed(1.f)
{
}

void Character::setSpeed(float speed)
{
	m_speed = speed;
}

float Character::getSpeed() const 
{
	return m_speed;
}
