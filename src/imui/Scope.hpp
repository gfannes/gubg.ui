#ifndef HEADER_imui_Scope_hpp_ALREADY_INCLUDED
#define HEADER_imui_Scope_hpp_ALREADY_INCLUDED

#include "imui/Reactor.hpp"
#include "imui/ID.hpp"
#include <map>

namespace imui { 

    template <typename Context>
        class Scope
        {
            public:
                using Self = Scope<Context>;
                using Reactor = imui::Reactor<Self>;

                Scope(Context &ctx): ctx_(ctx) {}

                Reactor &operator()(const ID &id)
                {
                    auto p = reactors_.emplace(id, *this);
                    return p.first->second;
                }

            private:
                Context &ctx_;
                using Reactors = std::map<ID, Reactor>;
                Reactors reactors_;
        };

} 

#endif
