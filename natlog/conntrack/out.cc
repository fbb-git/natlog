#include "conntrack.ih"

void Conntrack::out(Pattern const &pat, string const &endSeconds, 
                                        string const &endMicroSecs)
{
    ostringstream out1;
    out1 << "from " << 
            ShowTime(pat[1]) << ':' << pat[2] << " until " << 
            ShowTime(endSeconds) << ':' << endMicroSecs << 
                                        d_utcMarker << ':';

    ostringstream out2;
    out2 << ' ' << pat[4] << ':' << pat[6] << 
               " (via: " << pat[8] << ':' << pat[9] << ") "
        "to " << pat[5] << ':' << pat[7];

    imsg << out1.str() << "\n"
            "   " << out2.str() << endl;

    d_syslog << out1.str() << out2.str() << endl;
}
