#include "conntrack.ih"

// Example conntrack line: 
// [1338987414.52626 ]         [NEW] tcp      6 120 SYN_SENT 
//      src=192.168.1.4 dst=129.125.14.80 sport=59783 dport=22  [UNREPLIED] 
//      src=129.125.14.80 dst=129.125.100.246 sport=22 dport=59783

void Conntrack::run()
{
    Pattern pat(
    //     1        2      3
    "\\[(\\d+)\\.(\\d+).*(NEW|DESTROY).*"          // time: [1338899277.41469 ]
    //      4             5
    "src=(\\S+)\\s+dst=(\\S+)\\s+"          // source to nat,  dest
    //        6               7
    "sport=(\\d+)\\s+dport=(\\d+).*"        // source from,    dest port
    //      8               
    "dst=(\\S+).*"                          // natted source 
    //        9
    "dport=(\\d+)");                        // natted sport


    struct Record
    {
        string time1;
        string time2;
    };

    unordered_map<string, Record> record;

    d_conntrack.start();

    string utcMarker;
    if (d_options.time() == Options::UTC)
        utcMarker = " (UTC)";

    string line;
    while (getline(d_conntrack, line))
    {
        imsg << "LINE: " << line << endl;

        if (pat << line)
        {
            string key(pat[8] + pat[9]);

            if (pat[3] == "NEW")
                record[key] = Record {pat[1], pat[2]};
            else 
            {
                auto iter = record.find(key);
                if (iter == record.end())
                    wmsg << "UNAVAILABLE: " << line << endl;
                else
                {
                    ostringstream out;
                    out << "From " << 
                            ShowTime(iter->second.time1) << ':' << 
                                                        iter->second.time2 << 
                            " until " << 
                            ShowTime(pat[1]) << ':' << pat[2] << 
                                                        utcMarker << ":\n"

                        "    " << pat[4] << ':' << pat[6] << 
                                    " (via: " << pat[8] << ':' << pat[9] << ") "

                        "to " << pat[5] << ':' << pat[7];

                    imsg << out.str() << endl;
                    d_syslog << out.str() << endl;
                }
            }
        }
    }

}





