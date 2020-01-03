#ifndef HEADER_gubg_sfml_Label_hpp_ALREADY_INCLUDED
#define HEADER_gubg_sfml_Label_hpp_ALREADY_INCLUDED

#include <gubg/sfml/Types.hpp>

namespace gubg { namespace sfml { 

    class Label
    {
    public:
        Label() {}
        Label(FontPtr font)
        {
            set_font(font);
        }
        template <typename T>
        Label(FontPtr font, sf::Rect<T> bb)
        {
            set_font(font);
            set_bb(bb);
        }
        template <typename T>
        Label(FontPtr font, sf::Rect<T> bb, const std::string &str)
        {
            set_font(font);
            set_bb(bb);
            set_string(str);
        }

        void set_font(FontPtr font)
        {
            font_ = font;
            if (font_)
                text_.setFont(*font_);
        }
        template <typename T>
        void set_bb(sf::Rect<T> bb)
        {
#define unroll(x) x(left) x(top) x(width) x(height)
#define x(name) bb_.name = bb.name;
            unroll(x)
#undef x
#undef unroll
            text_.setCharacterSize(bb_.height);
            const auto underline_pos = font_ ? font_->getUnderlinePosition(bb_.height) : 0.0f;
            text_.setPosition(bb_.left, bb_.top-underline_pos);
        }
        void set_string(const std::string &str)
        {
            text_.setString(str);
        }

        template <typename Window>
        void draw(Window &window)
        {
            window.draw(text_);
        }

    private:
        FontPtr font_;
        sf::FloatRect bb_;
        sf::Text text_;
    };

} } 

#endif
