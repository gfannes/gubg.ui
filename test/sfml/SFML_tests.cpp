#include "catch.hpp"
#include "SFML/Graphics.hpp"

TEST_CASE("sfml tests", "[ut][sfml]")
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    sf::Clock windowClock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (windowClock.getElapsedTime().asSeconds() >= 1)
            window.close();

        window.clear();
        window.draw(shape);
        window.display();
    }
}
