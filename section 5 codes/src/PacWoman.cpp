#include "PacWoman.hpp"
#include <iostream>
PacWoman::PacWoman(sf::Texture& texture)
: m_visual(texture)
, m_isDying(false)
, m_isDead(false)
{
	setOrigin(20, 20); 
	
	m_runAnimator.addFrame(sf::IntRect(0, 32, 40, 40)); 
    m_runAnimator.addFrame(sf::IntRect(0, 72, 40, 40)); 

    m_dieAnimator.addFrame(sf::IntRect(0, 32, 40, 40));
    m_dieAnimator.addFrame(sf::IntRect(0, 72, 40, 40));
    m_dieAnimator.addFrame(sf::IntRect(0, 112, 40, 40));
    m_dieAnimator.addFrame(sf::IntRect(40, 112, 40, 40));
    m_dieAnimator.addFrame(sf::IntRect(80, 112, 40, 40));
    m_dieAnimator.addFrame(sf::IntRect(120, 112, 40, 40));
    m_dieAnimator.addFrame(sf::IntRect(160, 112, 40, 40));

    m_runAnimator.play(sf::seconds(0.25), true);
}

void PacWoman::die()
{
	if (!m_isDying)
	{
		m_dieAnimator.play(sf::seconds(1), false);
		m_isDying = true;
	} 
}

void PacWoman::reset()
{
	m_isDying = false;
	m_isDead = false;
	
	m_runAnimator.play(sf::seconds(0.25), true);
	m_runAnimator.animate(m_visual);
}

bool PacWoman::isDying() const
{
	return m_isDying;
}

bool PacWoman::isDead() const
{
	return m_isDead;
}

void PacWoman::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	
	if (!m_isDead)
	target.draw(m_visual, states);
}

void PacWoman::update(sf::Time delta)
{
    if (!m_isDead && !m_isDying)
    {
        m_runAnimator.update(delta);
        m_runAnimator.animate(m_visual);
    }
    else
    {
        m_dieAnimator.update(delta);
        m_dieAnimator.animate(m_visual);

        if (!m_dieAnimator.isPlaying())
        {
            m_isDying = false;
            m_isDead = true;
        }
    }
    Character::update(delta);
}
