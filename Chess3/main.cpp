#include <SFML/Graphics.hpp>
#include "Game.h"

unsigned int winWidth = 1920.f;
unsigned int winHeight = 1080.f;
const sf::Color bg(sf::Color::Black);

int main()
{
    Game game(winWidth, winHeight);
    sf::RenderWindow window(sf::VideoMode({ winWidth, winHeight}), "SFML works!");
    std::optional<sf::Event> event;

    while (window.isOpen())
    {
        while (event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            game.Update(window, event);
        }

        window.clear(bg);
        game.Update(window, std::nullopt);
        game.Draw(window);
        window.display();
    }
}