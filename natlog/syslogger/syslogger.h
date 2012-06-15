#ifndef INCLUDED_SYSLOGGER_
#define INCLUDED_SYSLOGGER_

#include <bobcat/syslogstream>

class Options;

class Syslogger: public FBB::SyslogStream
{
    public:
        Syslogger(Options &options);
};
        
#endif
