#ifndef HEADER_imui_Context_hpp_ALREADY_INCLUDED
#define HEADER_imui_Context_hpp_ALREADY_INCLUDED

#include "imui/Types.hpp"
#include "imui/AABB.hpp"
#include "imui/ReactorMgr.hpp"
#include "gubg/Transition.hpp"
#include "gubg/mss.hpp"
#include <set>
#include <cassert>

namespace imui { 

    template <typename Backend>
        class Context
        {
            private:
                static constexpr const char *logns = false ? "Context" : nullptr;

                using Self = Context<Backend>;
                using ReactorMgr = imui::ReactorMgr<Self>;
                using ReactorMgrs = std::set<ReactorMgr*>;
                using Reactor = imui::Reactor<ReactorMgr>;

            public:
                Context(typename Backend::Native &n): backend_(n) {}

                bool start_draw()
                {
                    MSS_BEGIN(bool, logns);

                    last_hot_.push();

                    mouse_.push();
                    MSS(backend_.get_mouse_position(mouse_.current()));
                    L(STREAM(mouse_.current()[0], mouse_.current()[1]));

                    MSS_END();
                }
                bool stop_draw()
                {
                    MSS_BEGIN(bool, logns);
                    MSS_END();
                }

                //During UI drawing and processing, all Reactors are sent to the Context via this way.
                bool process(Reactor &reactor)
                {
                    MSS_BEGIN(bool, logns);
                    if (reactor.state() == State::Fresh)
                    {
                        MSS_RETURN_OK();
                    }

                    reactor.set_state(State::Initialized);

                    const auto &mouse = mouse_.current();
                    if (reactor.tile.contains(mouse[0], mouse[1]))
                    {
                        L(reactor << " contains the mouse");
                        last_hot_.current() = &reactor;
                        if (last_hot_.same())
                            reactor.set_state(State::Hot);
                    }

                    MSS_END();
                }

                void insert(ReactorMgr *s) {reactor_mgrs_.insert(s);}
                void erase(ReactorMgr *s) {reactor_mgrs_.erase(s);}

                AABB_float aabb;

                template <typename Ftor>
                    void each_reactor(Ftor ftor)
                    {
                        for (auto ReactorMgr: reactor_mgrs_)
                        {
                            assert(!!ReactorMgr);
                            ReactorMgr->each_reactor(ftor);
                        }
                    }

            private:
                Backend backend_;

                ReactorMgrs reactor_mgrs_;

                using MouseTrans = gubg::Transition<MousePosition>;
                MouseTrans mouse_;

                using LastHot = gubg::Transition<Reactor *>;
                LastHot last_hot_;
        };

} 

#endif
