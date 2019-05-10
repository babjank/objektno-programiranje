#include "aux_states.h"
#include "game.h"
#include <sstream>
#include <string>


// Implementacija pomoćnih stanja.

WelcomeState::WelcomeState(Game *game,sf::RenderWindow& window):GameState(game,window)
{
    text1.setFont(font);
    text1.setString("Snake game");
    text1.setCharacterSize(40);
    text1.setOrigin(text1.getLocalBounds().width/2.f,text1.getLocalBounds().height/2.f);
    text1.setPosition(mWindow.getSize().x/2.f,mWindow.getSize().y/2.f);

    text2.setFont(font);
    text2.setString("by Bjanka Basic");
    text2.setCharacterSize(40);
    text2.setOrigin(text2.getLocalBounds().width/2.f,text2.getLocalBounds().height / 2.f);
    text2.setPosition(mWindow.getSize().x/2.f,mWindow.getSize().y/2.f+text1.getLocalBounds().height);

    text3.setFont(font);
    text3.setString("Hit any key to continue");
    text3.setCharacterSize(20);
    text3.setOrigin(text3.getLocalBounds().width / 2.f,text3.getLocalBounds().height / 2.f);
    text3.setPosition(mWindow.getSize().x - 200,mWindow.getSize().y - 70);

}
void WelcomeState::update(sf::Time dt)
{
}

void WelcomeState::handlePlayerInput(sf::Keyboard::Key code)
{
    mpGame->changeState(GameState::State::Playing);
}

void WelcomeState::render()
{
    mWindow.clear();
    mWindow.draw(text1);
    mWindow.draw(text2);
    mWindow.draw(text3);

    mWindow.display();
}
//-----------------------------------------------------------------

ExitingState::ExitingState(Game *game,sf::RenderWindow& window):GameState(game,window)
{
    timeRunning = 0;
    text.setFont(font);
    text.setString("Game over 3");
    text.setCharacterSize(40);
    text.setOrigin(text.getLocalBounds().width/2.f,text.getLocalBounds().height/2.f);
    text.setPosition(mWindow.getSize().x/2.f,mWindow.getSize().x/2.f);

}
void ExitingState::update(sf::Time dt)
{
    timeRunning += dt.asSeconds();
        if( timeRunning < 1.0 )
        {
            text.setString("Game over 3");
        }
        else if (timeRunning > 1.0 && timeRunning < 2.0 )
        {
            text.setString("Game over 2");
        }
        else if (timeRunning > 2.0 && timeRunning < 3.0)
        {
            text.setString("Game over 1");
        }
        else mWindow.close();
}

void ExitingState::handlePlayerInput(sf::Keyboard::Key code)
{
}

void ExitingState::render()
{
    mWindow.clear();
    mWindow.draw(text);
    mWindow.display();
}
//------------------------------------------------------------------
WonState::WonState(Game *game,sf::RenderWindow& window): GameState(game,window)
{

    text1.setFont(font);

    text2.setFont(font);
    text2.setString("Hit C to continue, X to exit");
    text2.setCharacterSize(20);
    text2.setOrigin(text2.getLocalBounds().width / 2.f,text2.getLocalBounds().height / 2.f);
    text2.setPosition(mWindow.getSize().x -200,mpGame->mWindow.getSize().y - 70);

}

void WonState::update(sf::Time dt)
{
}

void WonState::handlePlayerInput(sf::Keyboard::Key code)
{
    if(code == sf::Keyboard::C)
    {
        mpGame->changeState(GameState::State::Playing);
    }
    else if(code == sf::Keyboard::X)
    {
        mpGame->changeState(GameState::State::Exiting);
    }
}

void WonState::render()
{
    std::stringstream ss;
    ss<<"You won! The score = "<<std::to_string(mScore);
    text1.setString(ss.str());
    text1.setCharacterSize(40);
    text1.setOrigin(text1.getLocalBounds().width / 2,text1.getLocalBounds().height / 2);
    text1.setPosition(mWindow.getSize().x/ 2.f, mWindow.getSize().y/ 2.f);

    mWindow.clear();
    mWindow.draw(text1);
    mWindow.draw(text2);
    mWindow.display();

}

//---------------------------------------------------------------------
LostState::LostState(Game *game,sf::RenderWindow& window): GameState(game,window)
{
  text1.setFont(font);


  text2.setFont(font);
  text2.setString("Hit C to continue, X to exit");
  text2.setCharacterSize(20);
  text2.setOrigin(text2.getLocalBounds().width / 2.f,text2.getLocalBounds().height / 2.f);
  text2.setPosition(mWindow.getSize().x -200,mpGame->mWindow.getSize().y - 70);
}
void LostState::update(sf::Time dt)
{
}

void LostState::handlePlayerInput(sf::Keyboard::Key code)
{
  if(code == sf::Keyboard::C)
  {
      mpGame->changeState(GameState::State::Playing);
  }
  else if(code == sf::Keyboard::X)
  {
      mpGame->changeState(GameState::State::Exiting);
  }
}

void LostState::render()
{
    std::stringstream ss;
    ss<<"You Lost! The score = "<<std::to_string(mScore);
    text1.setString(ss.str());
    text1.setCharacterSize(40);
    text1.setOrigin(text1.getLocalBounds().width / 2,text1.getLocalBounds().height / 2);
    text1.setPosition(mWindow.getSize().x/ 2.f, mWindow.getSize().y/ 2.f);

    mWindow.clear();
    mWindow.draw(text1);
    mWindow.draw(text2);

    mWindow.display();
}
