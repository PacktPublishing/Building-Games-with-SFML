#include "Ghost.hpp"

Ghost::Ghost(sf::Texture& texture)
:m_visual(texture)
,m_isWeak(false)
,m_weaknessDuration(sf::Time::Zero)
//,m_pacWoman(pacWoman)
{
	setOrigin(20, 20);
	
	m_strongAnimator.addFrame(sf::IntRect(40, 32, 40, 40));
    m_strongAnimator.addFrame(sf::IntRect(80, 32, 40, 40));

    m_weakAnimator.addFrame(sf::IntRect(40, 72, 40, 40));
    m_weakAnimator.addFrame(sf::IntRect(80, 72, 40, 40));

    m_strongAnimator.play(sf::seconds(0.25), true);
    m_weakAnimator.play(sf::seconds(1), true);

}

void Ghost::setWeak(sf::Time duration)
{
	m_isWeak =true;
	m_weaknessDuration = duration;
}


bool Ghost::isWeak() const
{
	return m_isWeak;
}

void Ghost::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	
	target.draw(m_visual, states);
}

void Ghost::update(sf::Time delta)
{    
	
	if (m_isWeak)
    {
        m_weaknessDuration -= delta;

        if (m_weaknessDuration <= sf::Time::Zero)
        { 
            m_isWeak = false;
            m_strongAnimator.play(sf::seconds(0.25), true);
        }
    }
	
    if (!m_isWeak)
    {
        m_strongAnimator.update(delta);
        m_strongAnimator.animate(m_visual);
    }
    else
    {
        m_weakAnimator.update(delta);
        m_weakAnimator.animate(m_visual);
    }
}
