#pragma once

#include <memory>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio.hpp>

#include "State.hpp"
#include "Game.hpp"

class MainMenu : public Engine::State
{
private:
    std::shared_ptr<Context> m_context;
    sf::Text m_gameTitle;
    sf::Text m_playButton;
    sf::Text m_exitButton;

    bool m_isPlayButtonSelected;
    bool m_isPlayButtonPressed;

    bool m_isExitButtonSelected;
    bool m_isExitButtonPressed;

    sf::SoundBuffer m_clickSoundBuffer; // Almacena los datos del sonido
    sf::Sound m_clickSound;

public:
    MainMenu(std::shared_ptr<Context> &context);
    ~MainMenu();

    void Init() override;
    void ProcessInput() override;
    void Update(const sf::Time& deltaTime) override;
    void Draw() override;
};