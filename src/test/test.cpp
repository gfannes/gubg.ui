#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <thread>
#include <chrono>
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
                setProcessingInterval(sf::milliseconds(10));
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
                font_.loadFromFile("DejaVuSansMono.ttf");
            }

            void draw()
            {
                std::cout << "Drawing the window" << std::endl;
                std::cout << "Font: " << font_.getInfo().family << std::endl;
                sf::RenderWindow::draw(text_);
            }

        protected:
            void onCreate() override
            {
                std::cout << "Window was created" << std::endl;
                recorder.start();
                text_.setFont(font_);
                text_.setCharacterSize(50);
                text_.setColor(sf::Color::Green);
                text_.setPosition(200, 200);
                text_.setString("test");
            }
            void onResize() override
            {
                std::cout << "Window was resized" << std::endl;
            }
        private:
            app::Recorder recorder;
            sf::Font font_;
            sf::Text text_;
    };
} 

int main()
{
    app::Window window;

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

    return 0;
}
