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

                AABB_float aabb;

            private:
                Backend backend_;
        };

} 

#endif
