#include <SFML/Graphics.hpp>
#include "Game.h"

unsigned int winWidth = 1920.f;
unsigned int winHeight = 1080.f;
const sf::Color bg(sf::Color::Black);

int main()
{
    Game game(winWidth, winHeight);
    sf::RenderWindow window(sf::VideoMode({ winWidth, winHeight}), "SFML works!");

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(bg);
        game.Update(window);
        game.Draw(window);
        window.display();
    }
}