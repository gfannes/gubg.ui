#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <iostream>

namespace app { 

    class Recorder: public sf::SoundRecorder
    {
        public:
        protected:
            bool onProcessSamples(const sf::Int16 *samples, size_t size) override
            {
                std::cout << "Received " << size << " samples" << std::endl;
                for (int i = 0; i < size; ++i)
                    std::cout << samples[i] << ' ';
                std::cout << std::endl;
                return true;
            }
            bool onStart() override
            {
                std::cout << "onStart" << std::endl;
                return true;
            }
            void onStop() override
            {
                std::cout << "onStop" << std::endl;
            }
    };

    class Window: public sf::RenderWindow
    {
        public:
            Window()
            {
                sf::RenderWindow::create(sf::VideoMode(800, 600), "test");
            }

        protected:
            void onCreate() override
            {
                std::cout << "Window was created" << std::endl;
                recorder.start();
            }
            void onResize() override
            {
                std::cout << "Window was resized" << std::endl;
            }
        private:
            app::Recorder recorder;
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
