//
// Created by zuckerberg on 14/12/21.
//

#include "Game.h"

Game::Game():m_window(sf::VideoMode(640, 480), "Pac-Man CR") {
    if (!m_font.loadFromFile("../assets/font.ttf")) {
        throw std::runtime_error("Unable to load the font file!");
    }
    if (!m_logo.loadFromFile("../assets/logo.png")) {
        throw std::runtime_error("Unable to load the logo file!");
    }
    if (!m_texture.loadFromFile("../assets/texture.png")) {
        throw std::runtime_error("Unable to load the texture file!");
    }
    m_gameStates[GameState::NoCoin] = new NoCoinState(this);
    m_gameStates[GameState::GetReady] = new GetReadyState(this);
    m_gameStates[GameState::Playing] = new PlayingState(this);
    m_gameStates[GameState::Won] = new WonState(this);
    m_gameStates[GameState::Lost] = new LostState(this);
    changeGameState(GameState::NoCoin);
}

Game::~Game() {
    for (GameState* gameState: m_gameStates) {
        delete gameState;
    }
}

void Game::run() {
    sf::Clock frameClock;
    while (m_window.isOpen()) {
        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                m_window.close();
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::I) {
                    m_currentState->insertCoin();
                }
                else if (event.key.code == sf::Keyboard::S) {
                    m_currentState->pressButton();
                }
                else if (event.key.code == sf::Keyboard::Left) {
                    m_currentState->moveStick(sf::Vector2i(-1, 0));
                }
                else if (event.key.code == sf::Keyboard::Right) {
                    m_currentState->moveStick(sf::Vector2i(1, 0));
                }
                else if (event.key.code == sf::Keyboard::Up) {
                    m_currentState->moveStick(sf::Vector2i(0, -1));
                }
                else if (event.key.code == sf::Keyboard::Down) {
                    m_currentState->moveStick(sf::Vector2i(0, 1));
                }
            }
        }
        m_currentState->update(frameClock.restart());
        m_window.clear();
        m_currentState->draw(m_window);
        m_window.display();
    }
}

void Game::changeGameState(GameState::State gameState) {
    m_currentState = m_gameStates[gameState];
}

sf::Font& Game::getFont() {
    return m_font;
}

sf::Texture& Game::getTexture() {
    return m_texture;
}

sf::Texture& Game::getLogo() {
    return m_logo;
}