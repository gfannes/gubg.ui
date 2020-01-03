#include <gubg/sfml/FontMgr.hpp>
#include <gubg/sfml/Label.hpp>
#include "SFML/Graphics.hpp"
#include "catch.hpp"

TEST_CASE("sfml tests", "[ut][sfml][raw]")
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    gubg::sfml::FontMgr font_mgr;
    REQUIRE(font_mgr.load_font("gubg.ui/fonts/GenBasR.ttf", "myfont"));

    sf::Text text;

    gubg::sfml::Label label0{font_mgr.get_font("myfont"), sf::FloatRect{50,0,150,100}, "ag|"};
    gubg::sfml::Label label1{font_mgr.get_font("myfont"), sf::FloatRect{50,100,150,100}, "|BC"};

    sf::Clock windowClock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        const auto elapsed = windowClock.getElapsedTime().asSeconds();
        const auto duration = 0.5;

        window.clear();
        if (elapsed < 1*duration)
        {
            window.draw(shape);
        }
        else if (elapsed < 2*duration)
        {
            auto font = font_mgr.get_font("myfont");
            REQUIRE(!!font);
            text.setFont(*font);
            text.setString("abcdefg");
            text.setCharacterSize(50);
            window.draw(text);
        }
        else if (elapsed < 3*duration)
        {
            label0.draw(window);
            label1.draw(window);
        }
        else
            window.close();
        window.display();
    }
}
