#ifndef HEADER_ui_Markup_hpp_ALREADY_INCLUDED
#define HEADER_ui_Markup_hpp_ALREADY_INCLUDED

#include <vector>

namespace ui { 

    namespace markup { 
        struct Meta
        {
            size_t size = 0;
            size_t rix = 0;
            size_t cix = 0;
            int style = 0;
        };
        using Metas = std::vector<Meta>;
    } 

    class Markup
    {
        public:
            markup::Metas metas;

            Markup(size_t size): metas(size)
            {
                if (!metas.empty())
                    metas.front().size = size;
            }

        private:
    };

} 

#endif
