#include "world.h"

// Implementacija World klase.

#include <ctime>
#include <random>

// Implementacija klase World dolazi ovdje.

World::World(sf::Vector2i windowSize)
{
    mBlockSize = 20;
    mWindowSize = windowSize;
    mBounds[0].setSize({windowSize.x,mBlockSize});
    mBounds[0].setFillColor(sf::Color::White);
    mBounds[1].setSize({mBlockSize,windowSize.y});
    mBounds[1].setFillColor(sf::Color::White);
    mBounds[2].setSize({windowSize.x,mBlockSize});
    mBounds[2].setPosition(0,windowSize.y-mBlockSize);
    mBounds[2].setFillColor(sf::Color::White);
    mBounds[3].setSize({mBlockSize,windowSize.y});
    mBounds[3].setPosition(windowSize.x-mBlockSize,0);
    mBounds[3].setFillColor(sf::Color::White);

    mApple.setRadius(mBlockSize/2);
    mApple.setPosition(200,200);
    mApple.setFillColor(sf::Color::Red);
}

void World::respawnApple()
{
    int bb=(mWindowSize.x-2*mBlockSize)/mBlockSize;
    sf::Vector2f vect(mBlockSize+rand()%bb*mBlockSize,mBlockSize+rand()%bb*mBlockSize);
    mApple.setPosition(vect);
}

void World::update(Snake &snake)
{
    if((mApple.getPosition().x/mBlockSize)==snake.getPosition().x && (mApple.getPosition().y/mBlockSize)==snake.getPosition().y ){
        snake.extend();
        snake.increaseScore();
        respawnApple();

    }
    if(snake.getPosition().x==0 || snake.getPosition().x==(mWindowSize.x/mBlockSize -1) || snake.getPosition().y==0 || snake.getPosition().y==(mWindowSize.x/mBlockSize -1)){
        snake.lose();
        //snake.reset();
        respawnApple();
    }
}


void World::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    for(int i=0; i<4; ++i)
      target.draw(mBounds[i]);
    target.draw(mApple);
}
