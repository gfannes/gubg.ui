#ifndef HEADER_gubg_imgui_CStringMgr_hpp_ALREADY_INCLUDED
#define HEADER_gubg_imgui_CStringMgr_hpp_ALREADY_INCLUDED

#include <vector>
#include <sstream>

namespace gubg { namespace imgui { 

    class CStringMgr
    {
    public:
        void reset()
        {
            messages_.resize(0);
        }

        template <typename A>
        const char *operator()(const A &a)
        {
            oss_.str(""); oss_ << a;
            messages_.emplace_back(oss_.str());
            return messages_.back().c_str();
        }
        template <typename A, typename B>
        const char *operator()(const A &a, const B &b)
        {
            oss_.str(""); oss_ << a << b;
            messages_.emplace_back(oss_.str());
            return messages_.back().c_str();
        }
        template <typename A, typename B, typename C>
        const char *operator()(const A &a, const B &b, const C &c)
        {
            oss_.str(""); oss_ << a << b << c;
            messages_.emplace_back(oss_.str());
            return messages_.back().c_str();
        }
        template <typename A, typename B, typename C, typename D>
        const char *operator()(const A &a, const B &b, const C &c, const D &d)
        {
            oss_.str(""); oss_ << a << b << c << d;
            messages_.emplace_back(oss_.str());
            return messages_.back().c_str();
        }

    private:
        std::vector<std::string> messages_;
        std::ostringstream oss_;
    };

} } 

#endif
