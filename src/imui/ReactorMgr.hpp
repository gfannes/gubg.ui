#ifndef HEADER_imui_ReactorMgr_hpp_ALREADY_INCLUDED
#define HEADER_imui_ReactorMgr_hpp_ALREADY_INCLUDED

#include "imui/Reactor.hpp"
#include "imui/ID.hpp"
#include <map>

namespace imui { 

    template <typename Context>
        class ReactorMgr
        {
            private:
                static constexpr const char *logns = "ReactorMgr";

            public:
                using Self = ReactorMgr<Context>;
                using Reactor = imui::Reactor<Self>;

                ReactorMgr(Context &ctx)
                    : ctx_(ctx)
                {
                    ctx_.insert(this);
                }
                ~ReactorMgr()
                {
                    ctx_.erase(this);
                }

                Reactor &operator()(const ID &id)
                {
                    Reactor &reactor = reactors_.emplace(id, *this).first->second;
                    ctx_.process(reactor);
                    return reactor;
                }

                template <typename Ftor>
                    void each_reactor(Ftor ftor)
                    {
                        for (auto &p: reactors_)
                            ftor(p.second);
                    }

            private:
                Context &ctx_;
                using Reactors = std::map<ID, Reactor>;
                Reactors reactors_;
        };

} 

#endif
