#include "catch.hpp"
#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"
#include "gubg/imgui/SelectFile.hpp"
#include "gubg/macro/capture.hpp"
#include <memory>
#include <iostream>
#include <fstream>
#include <iomanip>

TEST_CASE("imgui-SFML tests", "[ut][imgui][sfml]")
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "");
    window.setVerticalSyncEnabled(true);
    ImGui::SFML::Init(window);

    sf::Color bgColor;

    float color[3] = { 0.f, 0.f, 0.f };

    // let's use char array as buffer, see next part
    // for instructions on using std::string with ImGui
    char windowTitle[255] = "ImGui + SFML = <3";

    std::filesystem::path filename;

    window.setTitle(windowTitle);
    window.resetGLStates(); // call it if you only draw ImGui. Otherwise not needed.
    sf::Clock deltaClock;
    sf::Clock windowClock;
    using Image_ptr = std::shared_ptr<sf::Image>;
    Image_ptr image;
    using Texture_ptr = std::shared_ptr<sf::Texture>;
    Texture_ptr texture;
    using Sprite_ptr = std::shared_ptr<sf::Sprite>;
    Sprite_ptr sprite;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (false && windowClock.getElapsedTime().asSeconds() >= 0.5)
            window.close();

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Sample window"); // begin window

        if (gubg::imgui::select_file("Image filename", filename))
        {
            Image_ptr img(new sf::Image);
            if (img->loadFromFile(filename.string()))
            {
                image = img;
                texture.reset(new sf::Texture);
                texture->loadFromImage(*image);
                sprite.reset(new sf::Sprite);
                sprite->setTexture(*texture, true);
                const auto wnd_size = window.getSize();
                const auto img_size = image->getSize();
                float x_scale = float(wnd_size.x)/img_size.x;
                float y_scale = float(wnd_size.y)/img_size.y;
                sprite->setScale(x_scale, y_scale);
            }
        }
        ImGui::SameLine();
        ImGui::Text(filename.string().c_str());

        if (image)
        {
            auto size = image->getSize();
            ImGui::Text("Image has size %d x %d", size.x, size.y);
            if (ImGui::Button("Convert"))
            {
                const auto img_size = image->getSize();
                auto fn = filename; fn += ".cpp";
                std::ofstream fo(fn);
                fo << "const int logo_auro[] = {" << std::endl;
                for (auto row = 0; row < img_size.y; ++row)
                {
                    for (auto col = 0; col < img_size.x; ++col)
                    {
                        auto color = image->getPixel(col, row);
                        int value = 0;
                        value <<= 5; value |= (color.r >> 3);
                        value <<= 6; value |= (color.g >> 2);
                        value <<= 5; value |= (color.b >> 3);
                        fo << " " << std::setw(6) << std::hex << std::showbase << value <<  ",";
                    }
                    fo << std::endl;
                }
                fo << "};" << std::endl;
            }
        }

        // Background color edit
        if (ImGui::ColorEdit3("Background color", color)) {
            // this code gets called if color value changes, so
            // the background color is upgraded automatically!
            bgColor.r = static_cast<sf::Uint8>(color[0] * 255.f);
            bgColor.g = static_cast<sf::Uint8>(color[1] * 255.f);
            bgColor.b = static_cast<sf::Uint8>(color[2] * 255.f);
        }

        // Window title text edit
        ImGui::InputText("Window title", windowTitle, 255);

        if (ImGui::Button("Update window title")) {
            // this code gets if user clicks on the button
            // yes, you could have written if(ImGui::InputText(...))
            // but I do this to show how buttons work :)
            window.setTitle(windowTitle);
        }
        ImGui::End(); // end window

        window.clear(bgColor); // fill background with color
        if (sprite)
            window.draw(*sprite);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();}
