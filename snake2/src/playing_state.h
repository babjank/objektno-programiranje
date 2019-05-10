#ifndef PLAYING_STATE_H
#define PLAYING_STATE_H

#include "game_state.h"
#include "snake.h"
#include "world.h"

// Naša glavna state-klasa. Veći dio koda iz
// prethodne Game klase završit će ovdje s manjim izmjenama.
class PlayingState : public GameState{
public:
    void update(sf::Time dt);
    void handlePlayerInput(sf::Keyboard::Key code);
    void render();

    PlayingState(Game * game, sf::RenderWindow& window);
private:
    World mWorld;
    Snake mSnake;
};


#endif // PLAYING_STATE_H
