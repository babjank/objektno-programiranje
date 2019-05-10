#include "game.h"


// Implementacija Game klase dolazi ovdje.

Game::Game() : mWindow(sf::VideoMode(800, 800), "SFML window"), mSnake(20), mWorld({800,800})
{
    mTimePerFrame=sf::seconds(0.099999f);
}

void Game::run()
{
    sf::Clock clock; // defaultni konstruktor starta sat
           // vrijeme od zadnjeg poziva funkciji update()
           sf::Time timeSinceLastUpdate = sf::Time::Zero;

           while(mWindow.isOpen())
           {
              processEvents();
              // stavi clock na nulu i vrati protekli interval
              timeSinceLastUpdate += clock.restart();
              // updatiraj eventualno više puta ako je iscrtavanje bilo sporo
              while(timeSinceLastUpdate > mTimePerFrame)
              {
                 timeSinceLastUpdate -= mTimePerFrame;
                 processEvents();
                 update(mTimePerFrame);
              }
              render();
           }

}

void Game::processEvents()
{
    sf::Event event;
        while (mWindow.pollEvent(event))
        {
            switch(event.type){
            case sf::Event::Closed:
                mWindow.close();
                break;
            case sf::Event::KeyPressed:
                handlePlayerInput(event.key.code);
                break;
            }
        }

}

void Game::update(sf::Time dt)
{
    mSnake.update();
    mWorld.update(mSnake);
}

void Game::render()
{
    mWindow.clear();
    mWindow.draw(mSnake);
    mWindow.draw(mWorld);
    mWindow.display();

}

void Game::handlePlayerInput(sf::Keyboard::Key code)
{
    if(code == sf::Keyboard::Up)
    {
        if(mSnake.getDirection()!=Direction::Down) mSnake.setDirection(Direction::Up);
    }
    else if(code == sf::Keyboard::Down)
    {
        if(mSnake.getDirection()!=Direction::Up) mSnake.setDirection(Direction::Down);
    }
    else if(code == sf::Keyboard::Right)
    {
         if(mSnake.getDirection()!=Direction::Left) mSnake.setDirection(Direction::Right);
    }
    else if(code == sf::Keyboard::Left)
    {
         if(mSnake.getDirection()!=Direction::Right) mSnake.setDirection(Direction::Left);
    }
    else mSnake.setDirection(Direction::None);
}
