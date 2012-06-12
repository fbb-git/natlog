#include "conntrack.ih"

// Example conntrack line: 
// [1338987414.52626 ]         [NEW] tcp      6 120 SYN_SENT 
//      src=192.168.1.4 dst=129.125.14.80 sport=59783 dport=22  [UNREPLIED] 
//      src=129.125.14.80 dst=129.125.100.246 sport=22 dport=59783

void Conntrack::run()
{
    Signal::instance().add(SIGTERM, *this);

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


    d_conntrack.start();

    string line;
    while (getline(d_conntrack, line))
    {
        imsg << "LINE: " << line << endl;

        if (pat << line)
        {
            string key(pat[8] + pat[9]);

            if (pat[3] == "NEW")
                d_record[key] = pat;
            else 
            {
                auto iter = d_record.find(key);
                if (iter == d_record.end())
                    wmsg << "UNAVAILABLE: " << line << endl;
                else
                {
                    out(iter->second, pat[1], pat[2]);
                    d_record.erase(iter);         // erase the processed element
                }
            }
        }
    }
}


