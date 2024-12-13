#pragma once

#include <list>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Audio.hpp>

class Snake : public sf::Drawable
{
public:
    Snake();
    ~Snake();

    void Init(const sf::Texture &texture);
    void Move(const sf::Vector2f &direction);
    bool IsOn(const sf::Sprite &other) const;
    void Grow(const sf::Vector2f &direction);
    bool IsSelfIntersecting() const;
    void PlayCollisionSound();
    void PlayEatSound();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:

    float GetRotationAngle(const sf::Vector2f &direction);
    std::list<sf::Sprite> m_body;
    std::vector<sf::Vector2f> m_directions;
    std::list<sf::Sprite>::iterator m_head;
    std::list<sf::Sprite>::iterator m_tail;
    sf::SoundBuffer m_collisionSoundBuffer;
    sf::Sound m_collisionSound;
    sf::SoundBuffer m_eatSoundBuffer;
    sf::Sound m_eatSound;
};
