#include "snake.h"

//  Implementacija klase Snake dolazi ovdje.

Snake::Snake(int blockSize):
    mlost(false) , mscore(0) , mlives(3) , msize(blockSize) , mdir(Direction::None)

{
// ? block size
    SnakeSegment s1(6,5);
    SnakeSegment s2(6,6);
    SnakeSegment s3(6,7);
    SnakeContainer ss;
    ss.push_back(s3);
    ss.push_back(s2);
    ss.push_back(s1);
    mSnakeBody=ss;

    mspeed=1;
}

sf::Vector2i Snake::getPosition()
{
    sf::Vector2i vect(mSnakeBody[0].x, mSnakeBody[0].y);
    return vect;
}

void Snake::extend()
{
    int last = mSnakeBody.size()-1;
    mSnakeBody.push_back(mSnakeBody[last]);
}

void Snake::reset()
{
    mSnakeBody.clear();
    SnakeSegment s1(6,5);
    SnakeSegment s2(6,6);
    SnakeSegment s3(6,7);
    SnakeContainer ss;
    ss.push_back(s3);
    ss.push_back(s2);
    ss.push_back(s1);
    mSnakeBody=ss;
    mdir=Direction::None;
    mlost=false; mscore=0; mlives=3;
}

void Snake::update()
{
    move();
    checkCollision();
}

void Snake::cut(int n)
{
    for(unsigned int i = 0;i<n;i++) mSnakeBody.pop_back();

}

void Snake::move()
{
    if(mdir==Direction::Up) {mSnakeBody.insert(mSnakeBody.begin(),SnakeSegment(mSnakeBody.front().x,mSnakeBody.front().y-mspeed)); mSnakeBody.pop_back();}
    else if(mdir==Direction::Down) {mSnakeBody.insert(mSnakeBody.begin(),SnakeSegment(mSnakeBody.front().x,mSnakeBody.front().y+mspeed)); mSnakeBody.pop_back();}
    else if(mdir==Direction::Right) {mSnakeBody.insert(mSnakeBody.begin(),SnakeSegment(mSnakeBody.front().x+mspeed,mSnakeBody.front().y)); mSnakeBody.pop_back();}
    else if(mdir==Direction::Left) {mSnakeBody.insert(mSnakeBody.begin(),SnakeSegment(mSnakeBody.front().x-mspeed,mSnakeBody.front().y)); mSnakeBody.pop_back();}
}

void Snake::checkCollision()
{
    for(int i=1; i<mSnakeBody.size(); ++i)
    {
        if(mSnakeBody.front().x==mSnakeBody[i].x && mSnakeBody.front().y==mSnakeBody[i].y){
            mlives--;
            if(mlives==0) reset();
            else cut(mSnakeBody.size()-i);
        }
    }
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    mbodyRect.setSize(sf::Vector2f(msize,msize));
    mbodyRect.setFillColor(sf::Color::Yellow);
    mbodyRect.setOutlineColor(sf::Color::Black);
    mbodyRect.setOutlineThickness(2);
    int x = mSnakeBody[0].x*msize;
    int y = mSnakeBody[0].y*msize;
    mbodyRect.setPosition(x, y);
    target.draw(mbodyRect);
    for(int i=1; i<mSnakeBody.size(); ++i){
        mbodyRect.setFillColor(sf::Color::Green);
        x = mSnakeBody[i].x*msize;
        y = mSnakeBody[i].y*msize;
        mbodyRect.setPosition(x, y);
        target.draw(mbodyRect);
     }
}
