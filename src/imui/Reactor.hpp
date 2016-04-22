#ifndef HEADER_imui_Reactor_hpp_ALREADY_INCLUDED
#define HEADER_imui_Reactor_hpp_ALREADY_INCLUDED

#include "imui/Tile.hpp"
#include "imui/State.hpp"
#include "imui/Events.hpp"
#include "gubg/debug.hpp"
#include <ostream>

namespace imui { 

    template <typename Mgr>
        class Reactor
        {
            private:
                static constexpr const char *logns = (false ? "Reactor" : nullptr);

            public:
                Tile tile;

                Reactor(Mgr &mgr): mgr_(mgr), state_(State::Fresh) {}

                template <typename Callback>
                    Reactor &on(Init, Callback cb)
                    {
                        S(logns);
                        if (state_ == State::Fresh)
                        {
                            L("We are still fresh: do initialization");
                            cb();
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
                            cb();
                        }
                        return *this;
                    }
                template <typename Callback>
                    Reactor &on(Clicked, Callback cb)
                    {
                        S(logns);
                        if (state_ == State::Clicked)
                        {
                            L("We are clicked");
                            cb();
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

                Mgr &mgr_;
        };

    template <typename Mgr>
        std::ostream &operator<<(std::ostream &os, const Reactor<Mgr> &reactor)
        {
            reactor.stream(os);
            return os;
        }

} 

#endif
