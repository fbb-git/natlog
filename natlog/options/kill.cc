#include "options.ih"

bool Options::kill() const
{
    if (not d_arg.option("terminate"))      // no terminate requested.
        return false;

    ifstream in;
    Exception::open(in, d_PIDfile);

    pid_t pid;
    if (not (in >> pid))
        throw Exception() << "no PID found in " << d_PIDfile;

    if (::kill(pid, SIGTERM) != 0)
        throw Exception() << "terminating " << d_arg.basename() << 
            " failed: " << errnodescr;

    return true;    
}
