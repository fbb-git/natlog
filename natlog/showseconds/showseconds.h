#ifndef INCLUDED_SHOWSECONDS_
#define INCLUDED_SHOWSECONDS_

#include <iosfwd>
#include <ctime>

#include "../options/options.h"

class ShowSeconds
{
    friend std::ostream &operator<<(std::ostream &out, 
                                    ShowSeconds const &showSeconds);

    std::string d_seconds;

    static std::string s_utcMarker;

    static void (*s_show)(std::ostream &out, std::string const &time);

    public:
        ShowSeconds(std::string const &seconds);
        ShowSeconds(time_t seconds);

        static void setFormat(Options::Time time);
        static std::string const &utcMarker();

    private:
            // all in time.cc
        static void rawTime(std::ostream &out, std::string const &seconds);
        static void utcTime(std::ostream &out, std::string const &seconds);
        static void localTime(std::ostream &out, std::string const &seconds);
};

inline std::string const &ShowSeconds::utcMarker()
{
    return s_utcMarker;
}

#endif


