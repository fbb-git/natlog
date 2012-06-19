#include "conntrack.ih"

// Example conntrack line: 
// [1338987414.52626 ]         [NEW] tcp      6 120 SYN_SENT 
//      src=192.168.1.4 dst=129.125.14.80 sport=59783 dport=22  [UNREPLIED] 
//      src=129.125.14.80 dst=129.125.100.246 sport=22 dport=59783

void Conntrack::run(ostream &parent)
{
    Signal::instance().add(SIGTERM, *this);

    Pattern pat(
    //     1        2      3
    "\\[(\\d+)\\.(\\d+).*(NEW|DESTROY).*"   // time: [1338899277.41469 ]
    //      4             5
    "src=(\\S+)\\s+dst=(\\S+)\\s+"          // source to nat,  dest
    //        6               7
    "sport=(\\d+)\\s+dport=(\\d+).*"        // source from,    dest port
    //      8               
    "dst=(\\S+).*"                          // natted source 
    //        9
    "dport=(\\d+)");                        // natted sport


    d_out << "starting " << d_options.conntrackPath() << endl;
    d_conntrack.start();

    string line;
    bool lines = false;

    while (getline(d_conntrack, line))
    {
        lines = true;

        imsg << "LINE: " << line << endl;

        if (pat << line)
        {
            string key(pat[8] + pat[9]);

            if (pat[3] == "NEW")
                d_connections.add(key, pat);
            else 
            {
                size_t idx = d_connections.find(key);
                if (idx == numeric_limits<size_t>::max())
                    wmsg << "UNAVAILABLE: " << line << endl;
                else
                {
                    log(*d_connections[idx], pat[1], pat[2]);
                    d_connections.erase(idx);  // erase processed element
                }
            }
        }
    }

    if (not lines && (d_conntrack.available() & Process::CHILD_CERR))
    {
        string line;
        getline(d_conntrack.cerr(), line);
        parent << line << endl;
    }
}








