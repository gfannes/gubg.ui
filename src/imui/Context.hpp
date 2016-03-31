#ifndef HEADER_imui_Context_hpp_ALREADY_INCLUDED
#define HEADER_imui_Context_hpp_ALREADY_INCLUDED

#include "imui/AABB.hpp"
#include "gubg/debug.hpp"

namespace imui { 

    template <typename Backend>
        class Context
        {
            public:
                Context(typename Backend::Native &n): backend_(n) {}

                void fill()
                {
                    using namespace sf;
                    S("Ctx");
                    const auto &v = backend_.native();
                    L(STREAM(v.getSize().x, v.getSize().y));
                    RectangleShape rect(Vector2f(990,990));
                    backend_.native().draw(rect);
                }

                AABB_float aabb;

            private:
                Backend backend_;
        };

} 

#endif
