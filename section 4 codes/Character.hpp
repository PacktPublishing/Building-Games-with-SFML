#ifndef PACWOMAN_CHARACTER_HPP
#define PACWOMAN_CHARACTER_HPP

#include "Maze.hpp"
#include <SFML/Graphics.hpp>

class Character : public sf::Drawable, public sf::Transformable
{
	public:
	Character();
	
	virtual void update(sf::Time delta); 
	void setDirection(sf::Vector2i direction); 
	sf::Vector2i getDirection() const; 
	void setMaze(Maze* maze); 
	
	void setSpeed (float speed);
	float getSpeed() const;
	
	private:
	float m_speed;
	Maze* m_maze; 
	
	sf::Vector2i m_currentDirection; 
	sf::Vector2i m_nextDirection; 
};

#endif // PACWOMAN_CHARACTER_HPP
