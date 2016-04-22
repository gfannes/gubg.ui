#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "catch.hpp"
#include "imui/Kit.hpp"
#include "imui/backend/SFML.hpp"
#include "SFML/Graphics.hpp"
#include <thread>
#include <chrono>
#include <iostream>

namespace  { 
    class Window: public sf::RenderWindow
    {
        public:
            Window(): ctx_(*this)
            {
                sf::RenderWindow::create(sf::VideoMode(400, 600), "imui::Context");
                sf::RenderWindow::setView(sf::View(sf::FloatRect(0,0, 400,600)));
            }

            void draw()
            {
                Kit::DrawSentry draw_sentry(ctx_);

                const float f = 50;
                const int r_end = 600/f;
                const int c_end = 400/f;

                for (int r = 0; r < r_end; ++r)
                {
                    for (int c = 0; c < c_end; ++c)
                    {
                        using namespace sf;
                        const Vector2f xy{f*c,f*r};
                        const Vector2f wh{f,f};
                        sf::RectangleShape rect(wh);
                        rect.setPosition(xy);
                        auto &reactor = mgr_(r*c_end+c);
                        reactor.on(imui::Init(), [&](){reactor.tile.set_aabb(xy.x,xy.y, wh.x,wh.y);});
                        reactor.on(imui::Hot(), [&](){rect.setFillColor(sf::Color::Red);});
                        reactor.on(imui::Clicked(), [&](){std::cout << "Clicked" << std::endl; r_ = r; c_ = c;});
                        if (r == r_ && c == c_)
                            rect.setFillColor(sf::Color::Blue);
                        sf::RenderWindow::draw(rect);
                    }
                }
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
            using Kit = imui::Kit<imui::backend::SFML>;
            Kit::Context ctx_;
            Kit::ReactorMgr mgr_{ctx_};
            int r_ = -1;
            int c_ = -1;
    };
} 

TEST_CASE("imui::Context tests", "[mt][ctx]")
{
    Window window;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
                std::cout << "clicked" << std::endl;
        }

        window.clear();
        window.draw();
        window.display();
        /* std::this_thread::sleep_for(std::chrono::milliseconds(20)); */
    }
    /* sf::RenderWindow window(sf::VideoMode(800, 600), "imui::Context"); */
}
