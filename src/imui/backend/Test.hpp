#ifndef HEADER_imui_backend_Test_hpp_ALREADY_INCLUDED
#define HEADER_imui_backend_Test_hpp_ALREADY_INCLUDED

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

        private:
            Native &native_;
    };

} } 

#endif
