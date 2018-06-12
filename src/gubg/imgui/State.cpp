#include "gubg/imgui/State.hpp"
#include <string>
#include <map>

namespace gubg { namespace imgui { 

    namespace details { 
        struct Data
        {
            using Ptr = std::shared_ptr<Data>;

            bool first = true;
            bool active = false;
            std::filesystem::path directory;
        };

        Data::Ptr goc_data_(const char *str_id)
        {
            static std::map<std::string, std::shared_ptr<Data>> data;
            auto &ptr = data[str_id];
            if (!ptr)
                ptr.reset(new Data);
            else
                ptr->first = false;
            return ptr;
        }
    } 

    State::State(const char *str_id): data_(details::goc_data_(str_id))
    {
    }

    bool State::first() const
    {
        return data_->first;
    }

    bool State::active() const
    {
        return data_->active;
    }
    void State::active(bool b)
    {
        data_->active = b;
    }

    const std::filesystem::path & State::directory() const
    {
        return data_->directory;
    }
    void State::directory(const std::filesystem::path &str)
    {
        data_->directory = str;
    }

} } 
