#include "Square.h"

Square::Square(int size, sf::Vector2f position)
{
    this->rect.setSize(sf::Vector2f(size, size));
    this->rect.setPosition(position);
    this->rect.setFillColor(sf::Color::Green);
    
}

Square::~Square()
{
}

void Square::SetGridPosition(int x, int y)
{
    this->x = x;
    this->y = y;
    
}

int Square::GetGridPositionX() const
{
    return this->x;
}

int Square::GetGridPositionY() const
{
    return this->y;
}

void Square::SetAliveStatus(bool status)
{
    this->isAlive = status;
    if(this->isAlive == ALIVE)this->rect.setFillColor(sf::Color::Red);
    if (this->isAlive == DEAD)this->rect.setFillColor(sf::Color::Green);
}

bool Square::getAliveStatus() const
{
    return this->isAlive;
}


