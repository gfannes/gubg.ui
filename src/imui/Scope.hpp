#ifndef HEADER_imui_Scope_hpp_ALREADY_INCLUDED
#define HEADER_imui_Scope_hpp_ALREADY_INCLUDED

#include "imui/Reactor.hpp"
#include "imui/ID.hpp"
#include <map>

namespace imui { 

    template <typename Context>
        class Scope
        {
            private:
                static constexpr const char *logns = "Scope";

            public:
                using Self = Scope<Context>;
                using Reactor = imui::Reactor<Self>;

                Scope(Context &ctx)
                    : ctx_(ctx)
                {
                    ctx_.insert(this);
                }
                ~Scope()
                {
                    ctx_.erase(this);
                }

                Reactor &operator()(const ID &id)
                {
                    S(logns);
                    Reactor &reactor = reactors_.emplace(id, *this).first->second;
                    L("Before processing by " << reactor);
                    ctx_.process(reactor);
                    L("After processing by ctx: " << reactor);
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
