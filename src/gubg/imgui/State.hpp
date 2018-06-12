#ifndef HEADER_gubg_imgui_State_hpp_ALREADY_INCLUDED
#define HEADER_gubg_imgui_State_hpp_ALREADY_INCLUDED

#include "gubg/std/filesystem.hpp"
#include <memory>

namespace gubg { namespace imgui { 

    namespace details { 
        struct Data;
    } 

    class State
    {
    public:
        State(const char *str_id);

        bool first() const;

        bool active() const;
        void active(bool b);

        const std::filesystem::path &directory() const;
        void directory(const std::filesystem::path &);

    private:
        std::shared_ptr<details::Data> data_;
    };

} } 

#endif
