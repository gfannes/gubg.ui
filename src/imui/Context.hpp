#ifndef HEADER_imui_Context_hpp_ALREADY_INCLUDED
#define HEADER_imui_Context_hpp_ALREADY_INCLUDED

#include "imui/AABB.hpp"

namespace imui { 

    template <typename Backend>
        class Context
        {
            public:
                Context(typename Backend::Window &window): backend_(window) {}

                AABB_float aabb;

            private:
                Backend backend_;
        };

} 

#endif
