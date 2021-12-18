//
// Created by zuckerberg on 14/12/21.
//

#ifndef PACMAN_CR_GAME_H
#define PACMAN_CR_GAME_H
#include "GameState.h"
#include <iostream>
#include <array>

class Game {
public:
    Game();
    ~Game();
    void run();
    void changeGameState(GameState::State gameState);
    sf::Font& getFont();
    sf::Texture& getLogo();
    sf::Texture& getTexture();

private:
    // Create the main window
    sf::RenderWindow m_window;
    GameState* m_currentState;
    std::array<GameState*, GameState::Count> m_gameStates;
    sf::Font m_font;
    sf::Texture m_logo;
    sf::Texture m_texture;
};


#endif //PACMAN_CR_GAME_H
