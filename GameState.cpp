//
// Created by zuckerberg on 14/12/21.
//

#include "GameState.h"
#include "Game.h"

template<typename T>
void centerOrigin(T& drawable) {
    sf::FloatRect bound = drawable.getLocalBounds();
    drawable.setOrigin(bound.width/2, bound.height/2);
}

GameState::GameState(Game* game):m_game(game) {

}

NoCoinState::NoCoinState(Game *game): GameState(game) {
    m_sprite.setTexture(game->getLogo());
    m_sprite.setPosition(20, 50);
    m_text.setFont(game->getFont());
    m_text.setString("Insert a coin!");
    centerOrigin(m_text);
    m_text.setPosition(240, 150);
    m_displayText = true;
}

GetReadyState::GetReadyState(Game *game): GameState(game) {
    m_text.setFont(game->getFont());
    m_text.setString("Press start when you're ready!");
    m_text.setCharacterSize(14);
    centerOrigin(m_text);
    m_text.setPosition(240, 240);
}

PlayingState::PlayingState(Game *game): GameState(game) {

}

WonState::WonState(Game *game): GameState(game) {
    m_text.setFont(game->getFont());
    m_text.setString("You won!");
    m_text.setCharacterSize(42);
    centerOrigin(m_text);
    m_text.setPosition(240, 120);
}

LostState::LostState(Game *game): GameState(game) {
    m_text.setFont(game->getFont());
    m_text.setString("You lost!");
    m_text.setCharacterSize(42);
    centerOrigin(m_text);
    m_text.setPosition(240, 120);
    m_countDown = sf::Time::Zero;
    m_countDownText.setFont(game->getFont());
    m_countDownText.setCharacterSize(12);
    centerOrigin(m_countDownText);
    m_countDownText.setPosition(240, 240);
}

Game* GameState::getGame() const {
    return m_game;
}

void NoCoinState::insertCoin() {
    getGame()->changeGameState(GameState::GetReady);
}

void NoCoinState::moveStick(sf::Vector2i direction) {

}

void NoCoinState::pressButton() {

}

void NoCoinState::draw(sf::RenderWindow& window) {
    window.draw(m_sprite);
    if (m_displayText) {
        window.draw(m_text);
    }
}

void NoCoinState::update(sf::Time delta) {
    static sf::Time buffer = sf::Time::Zero;
    buffer += delta;
    while (buffer >= sf::seconds(0.5)) {
        m_displayText = !m_displayText;
        buffer -= sf::seconds(1);
    }
}

void GetReadyState::insertCoin() {

}

void GetReadyState::moveStick(sf::Vector2i direction) {

}

void GetReadyState::pressButton() {
    getGame()->changeGameState(GameState::Playing);
}

void GetReadyState::draw(sf::RenderWindow& window) {
    window.draw(m_text);
}

void GetReadyState::update(sf::Time delta) {

}

void PlayingState::insertCoin() {

}

void PlayingState::moveStick(sf::Vector2i direction) {
    if (direction.x == 1) {
        getGame()->changeGameState(GameState::Won);
    }
    else if (direction.x == -1) {
        getGame()->changeGameState(GameState::Lost);
    }
}

void PlayingState::pressButton() {

}

void PlayingState::draw(sf::RenderWindow& window) {

}

void PlayingState::update(sf::Time delta) {

}

void WonState::insertCoin() {

}

void WonState::moveStick(sf::Vector2i direction) {

}

void WonState::pressButton() {

}

void WonState::draw(sf::RenderWindow& window) {
    window.draw(m_text);
}

void WonState::update(sf::Time delta) {
    static sf::Time buffer = sf::Time::Zero;
    buffer += delta;
    if (buffer >= sf::seconds(5)) {
        getGame()->changeGameState(GameState::GetReady);
    }
}

void LostState::insertCoin() {
    getGame()->changeGameState(GameState::GetReady);
}

void LostState::moveStick(sf::Vector2i direction) {

}

void LostState::pressButton() {

}

void LostState::draw(sf::RenderWindow& window) {
    window.draw(m_text);
    window.draw(m_countDownText);
}

void LostState::update(sf::Time delta) {
    m_countDown += delta;
    if (m_countDown.asSeconds() >= 10) {
        getGame()->changeGameState(GameState::NoCoin);
    }
    m_countDownText.setString("Insert a coin to continue! " + std::to_string(10 - static_cast<int>(m_countDown.asSeconds())));
}