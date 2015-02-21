#include "main.ih"

// Room for Args initialization
namespace   // the anonymous namespace can be used here
{
    Arg::LongOption longOptions[] =
    {
        Arg::LongOption("config", 'c'),

        Arg::LongOption("conntrack-command", Arg::Required),

        Arg::LongOption("conntrack-restart", Arg::Required),
        Arg::LongOption("help", 'h'),
        Arg::LongOption("no-daemon", Arg::None),
        Arg::LongOption("no-syslog", Arg::None),
        Arg::LongOption("pid-file", 'p'),
        Arg::LongOption("protocol", 'P'),
        Arg::LongOption("stdout", 's'),
        Arg::LongOption("syslog-facility", Arg::Required),
        Arg::LongOption("syslog-priority", Arg::Required),
        Arg::LongOption("syslog-tag", Arg::Required),
        Arg::LongOption("time", 't'),
        Arg::LongOption("verbose", Arg::None),
        Arg::LongOption("version", 'v'),
        Arg::LongOption("warn", 'w'),
    };

    auto longEnd = longOptions + sizeof(longOptions) / sizeof(longOptions[0]);
}

int main(int argc, char **argv)
try
{
    ArgConfig &arg = ArgConfig::initialize("c:hp:P:st:vw", 
                        longOptions, longEnd, argc, argv);
    
    arg.versionHelp(usage, Icmbuild::version, 1);

    NatFork fork;

    fork.run();
}
catch (exception const &err)
{
    cout << err.what() << endl;
    return 1;
}
catch (Options::ExitStatus status)
{
    return status;
}
catch (int x)
{
    return ArgConfig::instance().option("hv") ? 0 : x;
}



