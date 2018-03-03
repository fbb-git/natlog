#include "options.ih"

void Options::setBoolMembers()
{
    // d_useSyslog is set in `setSyslogParams'

    d_daemon = not d_arg.option(0, "no-daemon");
    d_stdout = d_verbose || d_arg.option('s');
    d_debug = d_arg.option(0, "debug");
}
