#include "options.ih"

Options::Options()
:
    d_arg(ArgConfig::instance())
{
        // the config file is:
        //      - where specified at 'c',   or:
        //      - ~/.natlogrc

    string config;
    if (not d_arg.option(&config, 'c'))
        config = s_defaultConfigPath;

    if (not (d_verbose = d_arg.option(0, "verbose")))
        imsg.off();

    if (not Stat(config))
        wmsg << "Configuration file `" << config << "' not found" << endl;
    else
    {
        imsg << "Used configuration file: `" << config << '\'' << endl;
        d_arg.open(config);
    }
    
    if (not d_arg.option('w'))
        wmsg.off();

    if (not d_arg.option(&d_syslogTag, "syslog-tag"))
        d_syslogTag = s_defaultSyslogIdent;

    d_useSyslog = not d_arg.option(0, "no-syslog");
    setSyslogFacility();
    setSyslogPriority();

    string time;
    if (not d_arg.option(&time, 't'))
        d_time = RAW;
    else setTime(time);

    if (emsg.count())           // encountered errors? Then quit.
        throw 1;


    if (d_verbose)
    {
        if (not d_useSyslog)
            cout << "No syslog messages\n";
        else
            cout <<
                "Writing syslog messages using syslog tag `" << 
                d_syslogTag << "', " "facility: " << facility() << ", "
                "priority: " << priority() << '\n';
    }

    if (not d_arg.option(&d_conntrackPath, "conntrack"))
        d_conntrackPath = s_defaultConntrackPath;
}

