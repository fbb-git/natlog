#include "main.ih"

// Room for Args initialization
namespace   // the anonymous namespace can be used here
{
    Arg::LongOption longOptions[] =
    {
        Arg::LongOption("help", 'h'),
        Arg::LongOption("version", 'v'),
        Arg::LongOption("daemon", 'd'),
        Arg::LongOption("conntrack", Arg::Required),
    };

    Arg::LongOption const *const longEnd =
                    longOptions + 
                    sizeof(longOptions) / sizeof(longOptions[0]);
}

char const g_config[] = "natlog.conf";

int main(int argc, char **argv)
try
{
    ArgConfig &arg = ArgConfig::initialize("c:dhv", 
                        longOptions, longEnd, argc, argv);
    
    arg.versionHelp(usage, Icmbuild::version, 1);

    string config = g_config;
    arg.option(&config, 'c');

    if (Stat(config))
        arg.open(config);

    if (string(arg[0]) != "conntrack")
        fmsg << "Currently only `conntrack' is available" << endl;

    string cmd;
    if (not arg.option(&cmd, "conntrack"))
    {
        if (not Stat(config))
            fmsg << "--contrack option missing" << endl; 
        else
            fmsg << "no --contrack option and no conntrack spec. "
                    "found in " << config << endl;
    }
    //cout << "conntrack command: " << cmd << '\n';


    Process conntrack(Process::COUT, cmd);

    conntrack.start();

    string line;
    Pattern pat(
    //     1        2      3
    "\\[(\\d+)\\.(\\d+).*(NEW|DESTROY).*"          // time: [1338899277.41469 ]
    //      4             5
    "src=(\\S+)\\s+dst=(\\S+)\\s+"          // source to nat,  dest
    //        6               7
    "sport=(\\d+)\\s+dport=(\\d+).*"        // source from,    dest port
    //        8
    "dport=(\\d+)");                        // natted sport


    struct Record
    {
        string time1;
        string time2;
    };

    unordered_map<string, Record> record;

    while (getline(conntrack, line))
    {
        if (pat << line)
        {
            if (pat[3] == "NEW")
                record[pat[8]] = Record {pat[1], pat[2]};
            else 
            {
                auto iter = record.find(pat[8]);
                if (iter == record.end())
                    cout << "UNAVAILABLE: " << line << '\n';
                else
                    cout << "From " << iter->second.time1 << ':' << 
                                                    iter->second.time2 << 
                            " until " << pat[1] << ':' << pat[2] << ":\n"
                        "    " << pat[4] << ':' << pat[6] << 
                                    " (via: " << pat[8] << ") "
                        "to " << pat[5] << ':' << pat[7] << '\n';
            }
        }
    }
}
catch (Errno const &err)
{
    cout << err.why() << '\n';
    return 1;
}
catch (...)
{
    return 1;
}
