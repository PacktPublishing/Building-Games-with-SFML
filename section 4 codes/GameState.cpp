#include "GameState.hpp"
#include "Game.hpp"

#include <iostream>

template <typename T>
void centerOrigin(T& drawable)
{
	sf::FloatRect bound = drawable.getLocalBounds();
	drawable.setOrigin(bound.width/2, bound.height/2);
}

GameState::GameState(Game* game)
:m_game(game)
{
}

NoCoinState::NoCoinState(Game* game)
:GameState(game)
{
	m_sprite.setTexture(game->getLogo());
	m_sprite.setPosition(20, 50);
	
	m_text.setFont(game->getFont());
	m_text.setString("Insert coin!");
	
	centerOrigin(m_text);
	m_text.setPosition(240, 150);
	
	m_displayText = true;
	
}

GetReadyState::GetReadyState(Game* game)
:GameState(game)
{
	m_text.setFont(game->getFont());
	m_text.setString("Press Start when you're ready...");
	m_text.setCharacterSize(14);
	
	centerOrigin(m_text);
	m_text.setPosition(240, 240);
}

PlayingState::PlayingState(Game* game)
:GameState(game)
//, m_pacWoman(game->getTexture())
//, m_ghost(game->getTexture())
, m_maze(game->getTexture())
, m_pacWoman(nullptr) 
{
	//m_pacWoman.move(100, 100);
	//m_ghost.move(200, 200);
	m_maze.loadLevel("large-level"); 
	m_pacWoman = new PacWoman(game->getTexture()); 
	m_pacWoman->setMaze(&m_maze); 
	m_pacWoman->setPosition(m_maze.mapCellToPixel(m_maze.getPacWomanPosition())); 
	
	for (auto ghostPosition : m_maze.getGhostPositions()) 
	{
		Ghost* ghost = new Ghost(game->getTexture());
		ghost->setMaze(&m_maze);
		ghost->setPosition(m_maze.mapCellToPixel(ghostPosition));
		
		m_ghosts.push_back(ghost);
	}
	
	m_camera.setSize(sf::Vector2f(480, 480)); 
}

PlayingState::~PlayingState() 
{
	delete m_pacWoman;
	
	for (Ghost* ghost : m_ghosts)
		delete ghost;
}

WonState::WonState(Game* game)
:GameState(game)
{
	m_text.setFont(game->getFont());
	m_text.setString("You Won!");
	m_text.setCharacterSize(42);
	
	centerOrigin(m_text);
	m_text.setPosition(240, 120);
}

LostState::LostState(Game* game)
:GameState(game)
{
	m_text.setFont(game->getFont());
	m_text.setString("You lost!");
	m_text.setCharacterSize(42);
	
	centerOrigin(m_text);
	m_text.setPosition(240, 120);
	
	m_countDownText.setFont(game->getFont());
	m_countDownText.setCharacterSize(12);
	
	centerOrigin(m_countDownText);
	m_countDownText.setPosition(240, 240);
}

Game* GameState::getGame() const
{
	return m_game;
}

void NoCoinState::insertCoin()
{
	getGame()->changeGameState(GameState::GetReady);
}
void NoCoinState::pressButton()
{
	
}
void NoCoinState::moveStick(sf::Vector2i direction)
{
	
}

void NoCoinState::update(sf::Time delta)
{
	static sf::Time timeBuffer = sf::Time::Zero;
	timeBuffer += delta;
	
	while (timeBuffer >= sf::seconds(0.5))
	{
		m_displayText = !m_displayText;
		timeBuffer -= sf::seconds(1);
	}	
}
void NoCoinState::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
	
	if (m_displayText)
	window.draw(m_text);
}

void GetReadyState::insertCoin()
{
	
}
void GetReadyState::pressButton()
{
	getGame()->changeGameState(GameState::Playing);
}
void GetReadyState::moveStick(sf::Vector2i direction)
{
	if (direction.x == -1)
		getGame()->changeGameState(GameState::Lost);
	else if (direction.x == 1)
		getGame()->changeGameState(GameState::Won);   
}
void GetReadyState::update(sf::Time delta)
{
	
}
void GetReadyState::draw(sf::RenderWindow& window)
{
	window.draw(m_text);
}

void PlayingState::insertCoin()
{
	//m_pacWoman.die();
}
void PlayingState::pressButton()
{
	//m_ghost.setWeak(sf::seconds(3));
}
void PlayingState::moveStick(sf::Vector2i direction)
{
	m_pacWoman->setDirection(direction);
}
void PlayingState::update(sf::Time delta)
{
	m_camera.setCenter(m_pacWoman->getPosition());
	
	if (m_camera.getCenter().x < 240)
		m_camera.setCenter(240, m_camera.getCenter().y);
	if (m_camera.getCenter().y < 240)
		m_camera.setCenter(m_camera.getCenter().x, 240);
		
	if (m_camera.getCenter().x > m_maze.getSize().x *32 - 240)
		m_camera.setCenter(m_maze.getSize().x *32 - 240, m_camera.getCenter().y);
		
	if (m_camera.getCenter().y > m_maze.getSize().y *32 - 240)
		m_camera.setCenter(m_camera.getCenter().x, m_maze.getSize().y *32 - 240);
			
	m_pacWoman->update(delta);
	
	for (Ghost* ghost : m_ghosts)
		ghost->update(delta);
				
}
void PlayingState::draw(sf::RenderWindow& window)
{
	window.setView(m_camera);
	window.draw(m_maze);
	window.draw(*m_pacWoman);
	
	for (Ghost* ghost : m_ghosts)
	window.draw(*ghost); 
}

void WonState::insertCoin()
{
	
}
void WonState::pressButton()
{
	
}
void WonState::moveStick(sf::Vector2i direction)
{
	
}
void WonState::update(sf::Time delta)
{
	static sf::Time timeBuffer = sf::Time::Zero;
	timeBuffer += delta;
	
	if (timeBuffer.asSeconds() > 5)
			getGame()->changeGameState(GameState::GetReady);
}
void WonState::draw(sf::RenderWindow& window)
{
	window.draw(m_text);
}

void LostState::insertCoin()
{
	
}
void LostState::pressButton()
{
	
}
void LostState::moveStick(sf::Vector2i direction)
{
	
}
void LostState::update(sf::Time delta)
{
	m_countDown += delta;
	
	if (m_countDown.asSeconds() >= 10)
		getGame()->changeGameState(GameState::GetReady);
	
	m_countDownText.setString("Insert a coin to continue... " + std::to_string(10- static_cast<int>(m_countDown.asSeconds())));
	
}
void LostState::draw(sf::RenderWindow& window)
{
	window.draw(m_text);
    window.draw(m_countDownText);
}
