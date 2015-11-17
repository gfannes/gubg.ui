#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <iostream>

namespace app { 
    class Window: public sf::RenderWindow
    {
        public:
            Window(): sf::RenderWindow(sf::VideoMode(800, 600), "test") {}

        protected:
            void onResize() override
            {
                std::cout << "Window was resized" << std::endl;
            }
    };
} 

int main()
{
    app::Window window;
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
