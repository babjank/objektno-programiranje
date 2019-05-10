#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

class Game{
public:
    Game();
    void run();
private:
    sf::RenderWindow mWindow;
    sf::Texture mTexture1;
    sf::Texture mTexture2;
    sf::Texture mTexture3;
    sf::Sprite mSprite1;
    sf::Sprite mSprite2;
    sf::Sprite mSprite3;
    float mKut;

    void processEvent();
    void update(sf::Time const & dt);
    void render();
};

#endif // GAME_H

