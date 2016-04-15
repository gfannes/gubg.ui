#ifndef HEADER_imui_Scope_hpp_ALREADY_INCLUDED
#define HEADER_imui_Scope_hpp_ALREADY_INCLUDED

#include "imui/Tile.hpp"
#include "imui/ID.hpp"
#include <map>

namespace imui { 

    template <typename Context>
        class Scope
        {
            public:
                using Self = Scope<Context>;
                using Tile = imui::Tile<Self>;

                Scope(Context &ctx): ctx_(ctx) {}

                Tile &goc(const ID &id)
                {
                    auto it = tiles_.find(id);
                    if
                }

            private:
                Context &ctx_;
                using Tiles = std::map<ID, Tile>;
                Tiles tiles_;
        };

} 

#endif
