#ifndef HEADER_imui_Context_hpp_ALREADY_INCLUDED
#define HEADER_imui_Context_hpp_ALREADY_INCLUDED

#include "imui/AABB.hpp"
#include "imui/Scope.hpp"
#include "gubg/mss.hpp"
#include <set>

namespace imui { 

    template <typename Backend>
        class Context
        {
            private:
                static constexpr const char *logns = "Context";

                using Self = Context<Backend>;
                using Scope = imui::Scope<Self>;
                using Scopes = std::set<Scope*>;

            public:
                Context(typename Backend::Native &n): backend_(n) {}

                bool process()
                {
                    MSS_BEGIN(bool, logns);
                    for (auto scope: scopes_)
                    {
                        MSS(!!scope);
                    }
                    MSS_END();
                }

                void insert(Scope *s) {scopes_.insert(s);}
                void erase(Scope *s) {scopes_.erase(s);}

                AABB_float aabb;

            private:
                Backend backend_;
                Scopes scopes_;
        };

} 

#endif
