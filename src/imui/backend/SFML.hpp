#ifndef HEADER_imui_backend_SMFL_hpp_ALREADY_INCLUDED
#define HEADER_imui_backend_SMFL_hpp_ALREADY_INCLUDED

#include "SFML/Window.hpp"

namespace imui { namespace backend { 

    namespace sfml { 
        using Window = ::sf::Window;
    } 

    class SFML
    {
        public:
            using Window = sfml::Window;

            SFML(Window &window): window_(window) {}

        private:
            Window &window_;
    };

} } 

#endif
