#ifndef HEADER_imui_AABB_hpp_ALREADY_INCLUDED
#define HEADER_imui_AABB_hpp_ALREADY_INCLUDED

namespace imui { 

    template <typename T>
        class AABB
        {
            public:
                T left = 0;
                T top = 0;
                T width = 0;
                T height = 0;

            private:
        };

    using AABB_float = AABB<float>;

} 

#endif
