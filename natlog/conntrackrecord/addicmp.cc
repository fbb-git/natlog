#include "conntrackrecord.ih"

void ConntrackRecord::addIcmp(std::string const &key, Pattern const &pat)
{
    bool sizes = pat.end() == idx(CTicmp::nFields);

    *firstFree() = new Record 
        {
            key, 
            pat[ idx(CTicmp::TIME1) ], 
            pat[ idx(CTicmp::TIME2) ], 
            "icmp",
            pat[ idx(CTicmp::SRC) ], 
            pat[ idx(CTicmp::DST) ], 
            "",                             // no source/dest ports
            "", 
            pat[ idx(CTicmp::NATSRC) ], 
            "",                             // no via-port
            sizes ? 
                stoul(pat[ idx(CTicmp::SENTBYTES) ]) : 0,
            sizes ? 
                stoul(pat[ idx(CTicmp::RECVDBYTES) ]) : 0,
        };
}
