#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "catch.hpp"
#include "imui/Context.hpp"
#include "imui/backend/SFML.hpp"
#include "SFML/Graphics.hpp"
#include <thread>
#include <chrono>
#include <iostream>

namespace  { 
    class Window: public sf::RenderWindow
    {
        public:
            Window()
            {
                sf::RenderWindow::create(sf::VideoMode(800, 600), "imui::Context");
            }

            void draw()
            {
                std::cout << "Drawing the window" << std::endl;
            }

        protected:
            void onCreate() override
            {
                std::cout << "Window was created" << std::endl;
            }
            void onResize() override
            {
                std::cout << "Window was resized" << std::endl;
            }
        private:
    };
} 

TEST_CASE("imui::Context tests", "[ut][imui]")
{
    Window window;
    imui::Context<imui::backend::SFML> ctx(window);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw();
        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    /* sf::RenderWindow window(sf::VideoMode(800, 600), "imui::Context"); */
}
