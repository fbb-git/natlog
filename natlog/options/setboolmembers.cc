#include "options.ih"

void Options::setBoolMembers()
{
    d_daemon = not d_arg.option(0, "no-daemon");
    d_verbose = d_arg.option(0, "verbose");
    d_stdout = d_verbose || d_arg.option('s');
    d_warnings = not d_arg.option('w');

    if (d_daemon && not d_useSyslog)
    {
        if (d_verbose || d_stdout)
            wmsg << "daemon mode: no messages to stdout" << endl;
        d_verbose = false;
        d_stdout = false;
        d_warnings = false;
    }

    if (not d_warnings)
        wmsg.off();

    if (not d_verbose)
        imsg.off();
    else
    {
        if (not d_useSyslog)
            cout << "No syslog messages\n";
        else
            cout <<
                "Writing syslog messages using syslog tag `" << 
                d_syslogTag << "', " "facility: " << facility() << ", "
                "priority: " << priority() << '\n';

    }
}
