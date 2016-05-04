#ifndef HEADER_tui_TextBox_hpp_ALREADY_INCLUDED
#define HEADER_tui_TextBox_hpp_ALREADY_INCLUDED

#include "tui/Markup.hpp"
#include "termbox.h"
#include <string>
#include <algorithm>

namespace tui { 
    class TextBox
    {
        public:
            TextBox(unsigned int x, unsigned int y, unsigned int w, unsigned int h): x_(x),y_(y), w_(w),h_(h)
        {
            set_style_(0);
        }

            void set_style_(int s)
            {
                switch (s)
                {
                    case 1:
                        cell_.bg = TB_DEFAULT;
                        cell_.fg = TB_GREEN;
                        break;
                    default:
                        cell_.bg = TB_DEFAULT;
                        cell_.fg = TB_YELLOW;
                        break;
                }
            }

            void draw(const std::string &str, const Markup &m)
            {
                if (h_ == 0)
                    return;

                const auto size = str.size();
                if (m.metas.size() != size)
                    return;

                for (size_t i = 0; i < size; i += m.metas[i].size)
                {
                    const auto &meta = m.metas[i];

                    if (meta.rix >= h_)
                        break;

                    if (meta.rix < 0)
                        continue;

                    set_style_(meta.style);

                    const auto cix_end = std::min<size_t>(meta.cix+meta.size, w_);
                    auto it = str.begin()+i;
                    for (size_t cix = meta.cix; cix < cix_end; ++cix, ++it)
                    {
                        cell_.ch = *it;
                        tb_put_cell(x_+cix, y_+meta.rix, &cell_);
                    }
                }
            }

        private:
            unsigned int x_ = 0;
            unsigned int y_ = 0;
            unsigned int w_ = 0;
            unsigned int h_ = 0;
            tb_cell cell_;
    };
} 

#endif
