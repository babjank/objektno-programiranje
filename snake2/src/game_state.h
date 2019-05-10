#ifndef GAME_STATE_H
#define GAME_STATE_H

// includes ...
#include <SFML/Graphics.hpp>

class Game;  // Samo referenca da se ne uvode cirkularne zavisnosti!

class GameState{
public:
    // Sva moguća stanja igre.
    enum State {
        Welcome,
        Playing,
        Won,
        Lost,
        Exiting,
        Count     // Count će dati broj stanja.
    };
    GameState(Game * game, sf::RenderWindow& window) : mpGame(game),mWindow(window),mScore(0)
    {
         if(!font.loadFromFile("Comfortaa-Bold.ttf")) throw std::runtime_error("Cannot load fonts Comfortaa-Bold.ttf");
    }

    // Metode koje ovise o stanju.
    virtual void update(sf::Time dt) = 0;
    virtual void handlePlayerInput(sf::Keyboard::Key code)= 0;
    virtual void render() = 0;

    void setScore(int score){mScore=score;}
protected:
    Game * mpGame;
    sf::RenderWindow& mWindow;
    sf::Font font;
    int mScore;
};

#endif // GAME_STATE_H

