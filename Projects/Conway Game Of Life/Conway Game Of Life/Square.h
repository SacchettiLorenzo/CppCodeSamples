#pragma once
#include <SFML/Graphics.hpp>

enum {DEAD, ALIVE};
class Square
{
public:
    Square(int size, sf::Vector2f position);
    ~Square();
    void SetGridPosition(int x, int y);
    int GetGridPositionX()const ;
    int GetGridPositionY() const;
    void SetAliveStatus(bool status);
    bool getAliveStatus() const;
    sf::RectangleShape rect;

    

private:
    int x, y;
    bool isAlive = false;
};

