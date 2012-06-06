#ifndef INCLUDED_OPTIONS_
#define INCLUDED_OPTIONS_

#include <iostream>
#include <string>

namespace FBB
{
    class ArgConfig;
}

class Options
{
    FBB::ArgConfig const &d_arg;

    bool d_verbose;

            // strings containing default file and other names
    static char s_defaultConfigFileName[];

    static Options *s_options;

    public:
        static Options &instance();

        Options(Options const &other) = delete;

        bool verbose() const;

    private:
        Options();
};

inline bool Options::verbose() const
{   
    return d_verbose;
}


#endif






