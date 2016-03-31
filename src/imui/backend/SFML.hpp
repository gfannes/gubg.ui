#ifndef HEADER_imui_backend_SMFL_hpp_ALREADY_INCLUDED
#define HEADER_imui_backend_SMFL_hpp_ALREADY_INCLUDED

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

        private:
            sfml::RenderWindow &rw_;
    };

} } 

#endif
