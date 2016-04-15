#ifndef HEADER_imui_ID_hpp_ALREADY_INCLUDED
#define HEADER_imui_ID_hpp_ALREADY_INCLUDED

namespace imui { 

    class ID
    {
        public:
            ID(unsigned int id): id_(id) {}

            bool operator<(const ID &rhs) const
            {
                return id_ < rhs.id_;
            }

        private:
            const unsigned int id_;
    };

} 

#endif
