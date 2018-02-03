#ifndef INCLUDED_SHOWSECONDS_
#define INCLUDED_SHOWSECONDS_

#include <iosfwd>

class ShowSeconds
{
    friend std::ostream &operator<<(std::ostream &out, 
                                    ShowSeconds const &showSeconds);

    size_t d_seconds;

    static std::string s_utcMarker;

    static void (*s_show)(std::ostream &out, size_t time);

    public:
        ShowSeconds();
        ShowSeconds(size_t seconds);

        static void setFormat();
        static std::string const &utcMarker();

        static std::string now();
        static void (*utcFormat())(std::ostream &, size_t);
        static void setFormat(void (*show)(std::ostream &, size_t));

    private:
            // all in time.cc
        static void rawTime(std::ostream &out,   size_t seconds);
        static void utcTime(std::ostream &out,   size_t seconds);
        static void localTime(std::ostream &out, size_t seconds);
};

inline std::string const &ShowSeconds::utcMarker()
{
    return s_utcMarker;
}

inline void ShowSeconds::setFormat(void (*show)(std::ostream &, size_t))
{
    s_show = show;
}

#endif


