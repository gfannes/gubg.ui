#ifndef HEADER_imui_backend_Test_hpp_ALREADY_INCLUDED
#define HEADER_imui_backend_Test_hpp_ALREADY_INCLUDED

#include "imui/Types.hpp"
#include "gubg/mss.hpp"

namespace imui { namespace backend { 

    namespace test { 
        class Native
        {
            public:
                Native(unsigned int width, unsigned int height): width(width), height(height) {}

                unsigned int width;
                unsigned int height;
        };
    } 

    class Test
    {
        public:
            using Native = test::Native;

            Test(Native &n): native_(n) {}

            bool get_mouse_position(MousePosition &pos)
            {
                MSS_BEGIN(bool);
                pos[0] = 0;
                pos[1] = 0;
                MSS_END();
            }

        private:
            Native &native_;
    };

} } 

#endif
