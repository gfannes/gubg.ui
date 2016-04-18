#ifndef HEADER_imui_State_hpp_ALREADY_INCLUDED
#define HEADER_imui_State_hpp_ALREADY_INCLUDED

#include <ostream>

namespace imui { 

    enum class State
    {
        Fresh,
        Initialized,
        Hot,
    };

    inline std::ostream &operator<<(std::ostream &os, State s)
    {
        switch (s)
        {
#define L_CASE(name) case State::name: os << #name; break
            L_CASE(Fresh);
            L_CASE(Initialized);
            L_CASE(Hot);
#undef L_CASE
            default: os << "Unkown state " << (int)s; break;
        }
        return os;
    }

} 

#endif
