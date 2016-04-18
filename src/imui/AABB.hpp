#ifndef HEADER_imui_AABB_hpp_ALREADY_INCLUDED
#define HEADER_imui_AABB_hpp_ALREADY_INCLUDED

namespace imui { 

    template <typename T>
        class AABB
        {
            private:
                using Self = AABB<T>;

            public:
                T left = 0;
                T top = 0;
                T width = 0;
                T height = 0;

                Self &set_aabb(T l, T t, T w, T h)
                {
                    left = l;
                    top = t;
                    width = w;
                    height = h;
                    return *this;
                }

                bool contains(T x, T y) const
                {
                    if (x < left) return false;
                    if (y < top) return false;
                    x -= width; y -= height;
                    if (x >= left) return false;
                    if (y >= top) return false;
                    return true;
                }

            private:
        };

    using AABB_float = AABB<float>;

} 

#endif
