#ifndef HEADER_gubg_sfml_FontMgr_hpp_ALREADY_INCLUDED
#define HEADER_gubg_sfml_FontMgr_hpp_ALREADY_INCLUDED

#include <gubg/sfml/Types.hpp>
#include <gubg/mss.hpp>
#include <map>

namespace gubg { namespace sfml { 

    class FontMgr
    {
    public:
        bool load_font(const std::string &filename, const std::string &name)
        {
            MSS_BEGIN(bool);
            auto it = name__font_.find(name);
            if (it == name__font_.end())
            {
                FontPtr ptr{new sf::Font};
                MSS(ptr->loadFromFile(filename));
                name__font_[name] = ptr;
            }
            MSS_END();
        }

        FontPtr get_font(const std::string &name) const
        {
            auto it = name__font_.find(name);
            if (it == name__font_.end())
                return FontPtr{};
            return it->second;
        }

    private:
        std::map<std::string, FontPtr> name__font_;
    };

} } 

#endif
