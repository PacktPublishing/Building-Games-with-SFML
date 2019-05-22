#ifndef PACWOMAN_ANIMATOR_HPP
#define PACWOMAN_ANIMATOR_HPP

#include <SFML/Graphics.hpp>

class Animator
{
public:
    Animator();

    void addFrame(sf::IntRect frame);

    void play(sf::Time duration, bool loop);
    bool isPlaying() const;

    void update(sf::Time delta);
    void animate(sf::Sprite& sprite);

private:
    std::vector<sf::IntRect> m_frames;

    bool m_isPlaying;
    sf::Time m_duration;
    bool m_loop;

    unsigned int m_currentFrame;
};

#endif // PACWOMAN_ANIMATOR_HPP
