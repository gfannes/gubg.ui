#ifndef HEADER_imui_Kit_hpp_ALREADY_INCLUDED
#define HEADER_imui_Kit_hpp_ALREADY_INCLUDED

#include "imui/Context.hpp"
#include "imui/DrawSentry.hpp"
#include "imui/ReactorMgr.hpp"
#include "imui/Tile.hpp"

namespace imui { 

    template <typename Backend_>
        class Kit
        {
            public:
                using Backend = Backend_;

                using Context = imui::Context<Backend>;
                using DrawSentry = imui::DrawSentry<Context>;
                using ReactorMgr = imui::ReactorMgr<Context>;
                using Reactor = imui::Reactor<Context>;
                using Tile = imui::Tile;

            private:
        };

} 

#endif
