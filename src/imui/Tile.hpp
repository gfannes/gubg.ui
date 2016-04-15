#ifndef HEADER_imui_Tile_hpp_ALREADY_INCLUDED
#define HEADER_imui_Tile_hpp_ALREADY_INCLUDED

#include "imui/AABB.hpp"

namespace imui { 

    template <typename Scope>
        class Tile
        {
            public:
                Tile(Scope &scope): scope_(scope) {}

            private:
                Scope &scope_;
        };

} 

#endif
