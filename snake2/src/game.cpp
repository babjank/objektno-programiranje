#include "game.h"

// Implementacija Game klase

Game::Game() : mWindow(sf::VideoMode(800, 800), "SFML window")
{
   // Ovdje alocirati sva stanja i postaviti pokazivač na trenutno stanje.

   mpGameStates[0]=new WelcomeState(this,mWindow);
   mpCurrentGameState=mpGameStates[0];
   mpGameStates[1]=new PlayingState(this,mWindow);
   mpGameStates[2]=new WonState(this,mWindow);
   mpGameStates[3]=new LostState(this,mWindow);
   mpGameStates[4]=new ExitingState(this,mWindow);

    mTimePerFrame=sf::seconds(1.f/11.f);
}

// Primjer run - metode. Zavisni dijelovi koda se delegiraju GameState klasama
// kroz pokazivač mpCurrentGameState.
void Game::run(){
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while(mWindow.isOpen())
    {
       processEvents();
       timeSinceLastUpdate += clock.restart();
       while(timeSinceLastUpdate > mTimePerFrame)
       {
          timeSinceLastUpdate -= mTimePerFrame;
          processEvents();
          mpCurrentGameState->update(mTimePerFrame);
       }
       // rendering
       mWindow.clear();
       mpCurrentGameState->render();
       mWindow.display();
    }
}

// obrada događaja
void Game::processEvents(){
   // implementacija
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        switch(event.type){
            case sf::Event::Closed:
                mWindow.close();
                break;
            case sf::Event::KeyPressed:
                mpCurrentGameState->handlePlayerInput(event.key.code);
                break;
            default:
                break;
            }
     }
}

GameState* Game::getState(GameState::State state)
{
    return mpGameStates[state];
}

void Game::changeTimePerFrame(bool won)
{
    if(won) mTimePerFrame=mTimePerFrame.asSeconds()*sf::seconds(5.f/6.f);
    else mTimePerFrame=sf::seconds(1.f/11.f);
}

Game::~Game()
{
    for(std::size_t i=0;i<GameState::State::Count;++i)
        delete mpGameStates[i];
}
