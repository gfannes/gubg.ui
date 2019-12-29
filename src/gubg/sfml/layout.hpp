#ifndef HEADER_gubg_sfml_layout_hpp_ALREADY_INCLUDED
#define HEADER_gubg_sfml_layout_hpp_ALREADY_INCLUDED

#include <SFML/Graphics/Rect.hpp>
#include <algorithm>

namespace gubg { namespace sfml { 

    template <typename T, typename Amount>
    sf::Rect<T> pop_top(sf::Rect<T> &rect, Amount amount)
    {
        amount = std::min<Amount>(amount, rect.height);
        auto res = rect;
        res.height = amount;
        rect.top += amount;
        rect.height -= amount;
        return res;
    }

    template <typename T, typename Amount>
    sf::Rect<T> pop_left(sf::Rect<T> &rect, Amount amount)
    {
        amount = std::min<Amount>(amount, rect.width);
        auto res = rect;
        res.width = amount;
        rect.left += amount;
        rect.width -= amount;
        return res;
    }

    template <typename T, typename Amount>
    void pop_border(sf::Rect<T> &rect, Amount amount)
    {
        amount = std::min<Amount>(amount, rect.height/2);
        amount = std::min<Amount>(amount, rect.width/2);
        rect.top += amount;
        rect.left += amount;
        rect.width -= 2*amount;
        rect.height -= 2*amount;
    }

    template <typename Drawable, typename T>
    void set_position(Drawable &drawable, const sf::Rect<T> &rect)
    {
        drawable.setPosition(rect.left, rect.top);
    }

} } 

#endif
