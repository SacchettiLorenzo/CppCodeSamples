#pragma once 
#include <iostream>
#include <algorithm>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "GridSpawner.h"
#include "Simulation.h"


int main()
{
    int width = 1920;
    int height = 1080;
    int squaresize = 20;
    int gap = 5;

    sf::RenderWindow window(sf::VideoMode(width, height), "SFML works!");

    sf::View view(sf::FloatRect(0, 0, width, height));


    GridSpawner g(gap, squaresize, width, height);

    Simulation s(g.getVecAddr(), &width, &height, &squaresize, &gap);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                int calculatedPositionX = event.mouseButton.x / (squaresize + gap);
                int calculatedPositionY = event.mouseButton.y / (squaresize + gap);

                std::vector<Square>::iterator it = std::find_if(g.getVecAddr()->begin(), g.getVecAddr()->end(), [calculatedPositionX, calculatedPositionY](Square s) {
                    return s.GetGridPositionX() == calculatedPositionX && s.GetGridPositionY() == calculatedPositionY;
                    });


                it->SetAliveStatus(!it->getAliveStatus());

            }

            if (event.type == sf::Event::Resized) {
                view.reset(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
                g = GridSpawner(gap, squaresize, window.getSize().x, window.getSize().y);
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Right) {
                    s.performSimulation();
                }
            }

        }

        window.clear();

        window.setView(view);


        for (Square q : *g.getVecAddr()) {

            window.draw(q.rect);
        }

        window.display();
    }

    return 0;
}


