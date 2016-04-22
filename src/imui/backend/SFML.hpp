#ifndef HEADER_imui_backend_SMFL_hpp_ALREADY_INCLUDED
#define HEADER_imui_backend_SMFL_hpp_ALREADY_INCLUDED

#include "imui/Types.hpp"
#include "gubg/mss.hpp"
#include "SFML/Window.hpp"

namespace imui { namespace backend { 

    namespace sfml { 
        using RenderWindow = ::sf::RenderWindow;
    } 

    class SFML
    {
        public:
            using Native = sfml::RenderWindow;

            SFML(Native &n): rw_(n) {}

            Native &native() {return rw_;}
            const Native &native() const {return rw_;}

            bool get_mouse_position(MousePosition &pos)
            {
                MSS_BEGIN(bool);
                const auto p = sf::Mouse::getPosition(rw_);
                pos[0] = p.x;
                pos[1] = p.y;
                MSS_END();
            }

        private:
            sfml::RenderWindow &rw_;
    };

} } 

#endif
