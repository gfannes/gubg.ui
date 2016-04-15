#ifndef HEADER_imui_Kit_hpp_ALREADY_INCLUDED
#define HEADER_imui_Kit_hpp_ALREADY_INCLUDED

#include "imui/Context.hpp"
#include "imui/Scope.hpp"
#include "imui/Tile.hpp"

namespace imui { 

    template <typename Backend_>
        class Kit
        {
            public:
                using Backend = Backend_;

                using Context = imui::Context<Backend>;
                using Scope = imui::Scope<Context>;
                using Tile = imui::Tile<Scope>;

            private:
        };

} 

#endif
