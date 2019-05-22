#ifndef PACWOMAN_CHARACTER_HPP
#define PACWOMAN_CHARACTER_HPP

#include <SFML/Graphics.hpp>

class Character : public sf::Drawable, public sf::Transformable
{
	public:
	Character();
	
	void setSpeed (float speed);
	float getSpeed() const;
	
	private:
	float m_speed;
	
};

#endif // PACWOMAN_CHARACTER_HPP
