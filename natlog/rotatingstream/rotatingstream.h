#ifndef INCLUDED_ROTATINGSTREAM_
#define INCLUDED_ROTATINGSTREAM_

#include <ostream>
#include "../rotatingstreambuf/rotatingstreambuf.h"

class RotatingStream: private RotatingStreambuf, public std::ostream
{
    public:
        RotatingStream(void (*header)(std::ostream &) = 0);
        void open(std::string const &name);
};

inline RotatingStream::RotatingStream(void (*header)(std::ostream &))
:
    RotatingStreambuf(header),
    std::ostream(this)
{}
        
inline void RotatingStream::open(std::string const &name)
{
    RotatingStreambuf::open(name);
}

#endif
