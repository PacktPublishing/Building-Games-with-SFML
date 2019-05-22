#include "Character.hpp"

Character::Character()
:m_maze(nullptr) 
,m_speed(25.f)
,m_currentDirection(1, 0) 
,m_nextDirection(0, 0) 
{
}

void Character::setMaze(Maze* maze) 
{
	m_maze = maze;
}

void Character::setSpeed(float speed)
{
	m_speed = speed;
}

float Character::getSpeed() const 
{
	return m_speed;
}

void Character::setDirection(sf::Vector2i direction) 
{
	m_nextDirection = direction;
}

sf::Vector2i Character::getDirection() const 
{
	return m_currentDirection;
}
void Character::update(sf::Time delta) 
{
	sf::Vector2f pixelPosition = getPosition();
	
	float pixelTraveled = getSpeed() * delta.asSeconds();
	
	sf::Vector2f nextPixelPosition = pixelPosition + sf::Vector2f(m_currentDirection) * pixelTraveled;
	setPosition(nextPixelPosition);
	
	sf::Vector2i cellPosition = m_maze->mapPixelToCell(pixelPosition);
	
	sf::Vector2f offset;
	offset.x = std::fmod(pixelPosition.x, 32) - 16;
	offset.y = std::fmod(pixelPosition.y, 32) - 16;
	
	if (m_maze->isWall(cellPosition + m_currentDirection))
	{		
		if ((m_currentDirection.x == 1 &&  offset.x > 0) ||
			(m_currentDirection.x == -1 && offset.x < 0) ||
			(m_currentDirection.y == 1 && offset.y > 0) ||
			(m_currentDirection.y == -1 && offset.y < 0))
		{
			setPosition(m_maze->mapCellToPixel(cellPosition));
		}
	}
	
	if (!m_maze->isWall(cellPosition + m_nextDirection) && m_currentDirection != m_nextDirection)
	{
		if ((!m_currentDirection.y && (offset.x > -2 && offset.x < 2)) ||
			(!m_currentDirection.x && (offset.y > -2 && offset.y < 2)))
		{
			setPosition(m_maze->mapCellToPixel(cellPosition));
			m_currentDirection = m_nextDirection;
			
			if (m_currentDirection == sf::Vector2i(1, 0))
            {
                setRotation(0);
                setScale(-1, 1);
            }
            else if (m_currentDirection == sf::Vector2i(0, 1))
            {
                setRotation(90);
                setScale(-1, 1);
            }
            else if (m_currentDirection == sf::Vector2i(-1, 0))
            {
                setRotation(0);
                setScale(1, 1);
            }
            else if (m_currentDirection == sf::Vector2i(0, -1))
            {
                setRotation(90);
                setScale(1, 1);
            }
		}
	}
}
