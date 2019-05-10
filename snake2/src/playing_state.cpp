#include "playing_state.h"
#include "game.h"

// Implementacija PlayingState klase

PlayingState::PlayingState(Game *game, sf::RenderWindow& window) : GameState(game,window), mSnake(20), mWorld({800,800})
{
}

void PlayingState::update(sf::Time dt)
{
    mSnake.update();
    mWorld.update(mSnake);

    if(mSnake.hasLost())
        {
            mpGame->getState(GameState::State::Won)->setScore(mSnake.getScore());
            mpGame->getState(GameState::State::Lost)->setScore(mSnake.getScore());
            mpGame->getState(GameState::State::Playing)->setScore(mSnake.getScore());

            if(mScore>100)
            {
                mpGame->changeTimePerFrame(true);
                mpGame->changeState(GameState::State::Won);
            }
            else
            {
                mpGame->changeTimePerFrame(false);
                mpGame->changeState(GameState::State::Lost);
            }
            mSnake.reset();
        }

}

void PlayingState::render()
{
    mWindow.clear();
    mWindow.draw(mSnake);
    mWindow.draw(mWorld);
    mWindow.display();

}


void PlayingState::handlePlayerInput(sf::Keyboard::Key code)
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
