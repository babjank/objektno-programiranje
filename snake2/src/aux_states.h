#ifndef AUX_STATES_H
#define AUX_STATES_H

#include "game_state.h"

// Sva pomoćna stanja (osim PlayingState). Njihove implementacije
// su prilično slične pa ih možemo grupirati u jedan file.

class WelcomeState : public GameState{
public:
    void update(sf::Time dt);
    void handlePlayerInput(sf::Keyboard::Key code);
    void render();

    WelcomeState(Game* game,sf::RenderWindow& window);
private:
    sf::Text text1;
    sf::Text text2;
    sf::Text text3;

};

class ExitingState : public GameState{
public:
    void update(sf::Time dt);
    void handlePlayerInput(sf::Keyboard::Key code);
    void render();

    ExitingState(Game* game,sf::RenderWindow& window);
private:
    sf::Text text;
    float timeRunning;
};

class WonState : public GameState{
public:
    void update(sf::Time dt);
    void handlePlayerInput(sf::Keyboard::Key code);
    void render();

    WonState(Game* game,sf::RenderWindow& window);
private:
    sf::Text text1, text2;
};

class LostState : public GameState{
public:
    void update(sf::Time dt);
    void handlePlayerInput(sf::Keyboard::Key code);
    void render();

    LostState(Game* game,sf::RenderWindow& window);
private:
    sf::Text text1, text2;
};

#endif // AUX_STATES_H
