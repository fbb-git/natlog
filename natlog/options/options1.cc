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
        config = User().homedir() + s_defaultConfigFileName;

    if (Stat(config))
        d_arg.open(config);

    if (not (d_verbose = d_arg.option(0, "verbose")))
        imsg.off();

    if (not d_arg.option(&d_syslogIdent, "syslog-ident"))
        d_syslogIdent = s_defaultSyslogIdent;

    d_useSyslog = not d_arg.option(0, "no-syslog");
    setSyslogFacility();
    setSyslogPriority();

    if (emsg.count())           // encountered errors? Then quit.
        throw 1;
    
    if (not d_arg.option(&d_conntrackPath, "conntrack"))
        d_conntrackPath = s_defaultConntrackPath;
}
