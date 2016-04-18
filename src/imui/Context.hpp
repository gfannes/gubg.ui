#ifndef HEADER_imui_Context_hpp_ALREADY_INCLUDED
#define HEADER_imui_Context_hpp_ALREADY_INCLUDED

#include "imui/AABB.hpp"
#include "imui/Scope.hpp"
#include "gubg/mss.hpp"
#include <set>
#include <cassert>

namespace imui { 

    template <typename Backend>
        class Context
        {
            private:
                static constexpr const char *logns = "Context";

                using Self = Context<Backend>;
                using Scope = imui::Scope<Self>;
                using Scopes = std::set<Scope*>;
                using Reactor = imui::Reactor<Scope>;

            public:
                Context(typename Backend::Native &n): backend_(n) {}

                bool reduce()
                {
                    MSS_BEGIN(bool, logns);

                    auto update_state = [&](Reactor &reactor)
                    {
                        L(reactor);
                        if (last_hot_ == &reactor)
                        {
                            reactor.set_state(State::Hot);
                        }
                    };
                    each_reactor(update_state);

                    last_hot_ = nullptr;

                    MSS_END();
                }

                //During UI drawing and processing, all Reactors are sent to the Context via this way.
                bool process(Reactor &reactor)
                {
                    MSS_BEGIN(bool);
                    if (reactor.state() == State::Fresh)
                    {
                        MSS_RETURN_OK();
                    }
                    if (reactor.tile.contains(mouse_[0], mouse_[1]))
                        last_hot_ = &reactor;
                    MSS_END();
                }

                void insert(Scope *s) {scopes_.insert(s);}
                void erase(Scope *s) {scopes_.erase(s);}

                AABB_float aabb;

                template <typename Ftor>
                    void each_reactor(Ftor ftor)
                    {
                        for (auto scope: scopes_)
                        {
                            assert(!!scope);
                            scope->each_reactor(ftor);
                        }
                    }

            private:
                Backend backend_;
                Scopes scopes_;
                Reactor *last_hot_ = nullptr;
                std::array<unsigned int, 2> mouse_{};
        };

} 

#endif
