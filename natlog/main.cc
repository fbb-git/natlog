#include "main.ih"

namespace   // the anonymous namespace can be used here
{
    Arg::LongOption longOptions[] =
    {
        Arg::LongOption("config", 'c'),

        Arg::LongOption("conntrack-ip-header-size", Arg::Required),
        Arg::LongOption("conntrack-command", Arg::Required),
        Arg::LongOption("conntrack-device", Arg::Required),
        Arg::LongOption("conntrack-restart", Arg::Required),
        Arg::LongOption("debug", Arg::None),
        Arg::LongOption("help", 'h'),
        Arg::LongOption("log", Arg::Required),
        Arg::LongOption("log-data", Arg::Required),
        Arg::LongOption("log-rotate", Arg::Required),
        Arg::LongOption("no-daemon", Arg::None),
        Arg::LongOption("pid-file", 'p'),
        Arg::LongOption("protocol", 'P'),
        Arg::LongOption("stdout", 's'),
        Arg::LongOption("syslog-facility", Arg::Required),
        Arg::LongOption("syslog-priority", Arg::Required),
        Arg::LongOption("syslog-tag", Arg::Required),
        Arg::LongOption("terminate", Arg::None),
        Arg::LongOption("time", 't'),
        Arg::LongOption("ttl", 'T'),
        Arg::LongOption("verbose", 'V'),
        Arg::LongOption("version", 'v'),
//        Arg::LongOption("warn", 'w'),
    };

    auto longEnd = longOptions + size(longOptions);
}

int main(int argc, char **argv)
try
{
    ArgConfig &arg = ArgConfig::initialize("c:hp:P:st:T:vV", 
                        longOptions, longEnd, argc, argv);
    
    arg.versionHelp(usage, Icmbuild::version, 
                    arg.option(0, "terminate") ? 0 : 1);

    if (Options::instance().kill())
        return 0;

    NatFork natfork;

    natfork.run();
}
catch (exception const &err)
{
    cout << err.what() << endl;
    return 1;
}
catch (int x)
{
    return ArgConfig::instance().option("hv") ? 0 : x;
}
