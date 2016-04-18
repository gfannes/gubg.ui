#ifndef HEADER_imui_Reactor_hpp_ALREADY_INCLUDED
#define HEADER_imui_Reactor_hpp_ALREADY_INCLUDED

#include "imui/Tile.hpp"
#include "imui/State.hpp"
#include "imui/Events.hpp"
#include "gubg/debug.hpp"
#include <ostream>

namespace imui { 

    template <typename Scope>
        class Reactor
        {
            private:
                static constexpr const char *logns = "Reactor";

            public:
                Tile tile;

                Reactor(Scope &scope): scope_(scope), state_(State::Fresh) {}

                template <typename Callback>
                    Reactor &on(Init, Callback cb)
                    {
                        S(logns);
                        if (state_ == State::Fresh)
                        {
                            L("We are still fresh: do initialization");
                            cb(tile);
                            set_state(State::Initialized);
                        }
                        return *this;
                    }
                template <typename Callback>
                    Reactor &on(Hot, Callback cb)
                    {
                        S(logns);
                        if (state_ == State::Hot)
                        {
                            L("We are hot");
                            cb(tile);
                        }
                        return *this;
                    }

                void stream(std::ostream &os) const
                {
                    os << this << ": State: " << state_;
                }

                State state() const {return state_;}
                void set_state(State s)
                {
                    S(logns);
                    state_ = s;
                    L("Reactor " << this << " is now " << state_);
                }

            private:
                State state_;

                Scope &scope_;
        };

    template <typename Scope>
        std::ostream &operator<<(std::ostream &os, const Reactor<Scope> &reactor)
        {
            reactor.stream(os);
            return os;
        }

} 

#endif
