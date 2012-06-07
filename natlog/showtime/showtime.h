#ifndef INCLUDED_SHOWTIME_
#define INCLUDED_SHOWTIME_

#include <iosfwd>

#include "../options/options.h"

class ShowTime
{
    friend std::ostream &operator<<(std::ostream &out, 
                                    ShowTime const &showTime);

    std::string const &d_seconds;

    static void (*s_show)(std::ostream &out, std::string const &time);

    public:
        ShowTime(std::string const &seconds);

        static void setDisplay(Options::Time time);

    private:
            // all in time.cc
        static void rawTime(std::ostream &out, std::string const &seconds);
        static void utcTime(std::ostream &out, std::string const &seconds);
        static void localTime(std::ostream &out, std::string const &seconds);
};

inline void ShowTime::setDisplay(Options::Time time)
{
    s_show = 
        time == Options::RAW ? rawTime :
                Options::UTC ? utcTime :
                               localTime;
}
        
#endif
