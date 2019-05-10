#include "game.h"
#include <cmath>

#include <stdexcept>

Game::Game() : mWindow(sf::VideoMode(800, 800), "SFML window")
{
    if (!mTexture1.loadFromFile("SunRed.png"))
        throw std::runtime_error("Cannot open file SunRed.png!");
    if (!mTexture2.loadFromFile("planet1.png"))
        throw std::runtime_error("Cannot open file planet1.png!");
    if (!mTexture3.loadFromFile("Plane.png"))
        throw std::runtime_error("Cannot open file Plane.png!");

    mSprite1.setTexture(mTexture1);
    mSprite2.setTexture(mTexture2);
    mSprite3.setTexture(mTexture3);

    sf::Vector2f scale1 = mSprite1.getScale();
    sf::Vector2f scale2 = mSprite2.getScale();
    sf::Vector2f scale3 = mSprite3.getScale();

    mSprite1.setOrigin(400, 400);
    mSprite2.setOrigin(250, 250);
    mSprite3.setOrigin(221.5, 151);

    mSprite1.setPosition(400, 400);
    mSprite2.setPosition(650, 400);
    mSprite3.setPosition(650, 400-100);

    mSprite1.setScale({scale1.x*0.15f, scale1.y*0.15f});
    mSprite2.setScale({scale2.x*0.15f, scale2.y*0.15f});
    mSprite3.setScale({scale3.x*0.15f, scale3.y*0.15f});

    mSprite3.setRotation(mSprite3.getRotation()+90);
}

void Game::run(){
    sf::Clock clock;
    while(mWindow.isOpen())
    {
       sf::Time dt = clock.restart();
       processEvent();
       update(dt);
       render();
    }
}

void Game::processEvent()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        if (event.type==sf::Event::Closed)
            mWindow.close();
    }
}

void Game::update(sf::Time const & dt)
{
    sf::Vector2f pos1(0,0), pos2(0,0);
    mKut+=dt.asSeconds()*(M_PI)/30;
    pos1.x=400+250*cos(mKut);
    pos1.y=400+250*sin(mKut);
    mSprite2.setPosition(pos1);
    mSprite2.rotate(dt.asSeconds()*72);

    pos2.x=pos1.x+100*cos(mKut*30);
    pos2.y=pos1.y+100*sin(mKut*30);
    mSprite3.setPosition(pos2);
    mSprite3.rotate(dt.asSeconds()*180);
}

void Game::render()
{
    mWindow.clear();
    mWindow.draw(mSprite1);
    mWindow.draw(mSprite2);
    mWindow.draw(mSprite3);
    mWindow.display();
}
