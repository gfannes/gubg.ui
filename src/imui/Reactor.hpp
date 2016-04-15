#ifndef HEADER_imui_Reactor_hpp_ALREADY_INCLUDED
#define HEADER_imui_Reactor_hpp_ALREADY_INCLUDED

#include "imui/Tile.hpp"

namespace imui { 

    struct Init
    {
    };

    template <typename Scope>
        class Reactor
        {
            public:
                Tile tile;

                Reactor(Scope &scope): scope_(scope), state_(State::Fresh) {}

                template <typename Callback>
                    Reactor &on(Init, Callback cb)
                    {
                        if (state_ == State::Fresh)
                        {
                            cb(tile);
                            state_ = State::Initialized;
                        }
                        return *this;
                    }

            private:
                enum class State
                {
                    Fresh, Initialized,
                };

                State state_;

                Scope &scope_;
        };

} 

#endif
