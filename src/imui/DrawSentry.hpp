#ifndef HEADER_imui_DrawSentry_hpp_ALREADY_INCLUDED
#define HEADER_imui_DrawSentry_hpp_ALREADY_INCLUDED

namespace imui { 

    template <typename Context>
        class DrawSentry
        {
            public:
                DrawSentry(Context &ctx): ctx_(ctx)
                {
                    ctx_.start_draw();
                }
                ~DrawSentry()
                {
                    ctx_.stop_draw();
                }
            private:
                Context &ctx_;
        };

} 

#endif
