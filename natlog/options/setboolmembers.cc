#include "options.ih"

void Options::setBoolMembers()
{
    // d_useSyslog is set in `openSyslog'

    d_daemon = not d_arg.option(0, "no-daemon");
    d_verbose = d_arg.option(0, "verbose");
    d_stdout = d_verbose || d_arg.option('s');
    d_warnings = not d_arg.option('w');

    if (d_daemon)
    {
        if (not d_useSyslog)
            d_verbose = false;
        d_stdout = false;
        d_warnings = false;
    }
}

//        if (d_useSyslog)
//        {
//            if (d_verbose)
//            {
//                cout <<
//                    "Syslog messages use syslog tag `" << 
//                    d_syslogTag << "', " "facility: " << facility() << ", "
//                    "priority: " << priority() << '\n';
//                wmsg << "daemon mode: verbose messages to syslog" << endl;
//            }
//        }
//        else
//        {
//            if (d_verbose)
//                wmsg << "daemon mode: no verbose messages" << endl;
//            d_verbose = false;
//        }
//    if (not d_useSyslog and d_verbose)
//        cout << "No syslog messages" << endl;

