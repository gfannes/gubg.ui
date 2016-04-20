#ifndef HEADER_imui_Context_hpp_ALREADY_INCLUDED
#define HEADER_imui_Context_hpp_ALREADY_INCLUDED

#include "imui/AABB.hpp"
#include "imui/Scope.hpp"
#include "gubg/Transition.hpp"
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
                using MousePosition = std::array<unsigned int, 2>;

                Context(typename Backend::Native &n): backend_(n) {}

                bool process(const MousePosition &mouse)
                {
                    MSS_BEGIN(bool, logns);

                    mouse_.push(mouse);
                    last_hot_.push();

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

                    const auto &mouse = mouse_.current();
                    if (reactor.tile.contains(mouse[0], mouse[1]))
                    {
                        last_hot_.current() = &reactor;
                        if (last_hot_.same())
                            reactor.set_state(State::Hot);
                    }

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

                using MouseTrans = gubg::Transition<MousePosition>;
                MouseTrans mouse_;

                using LastHot = gubg::Transition<Reactor *>;
                LastHot last_hot_;
        };

} 

#endif
