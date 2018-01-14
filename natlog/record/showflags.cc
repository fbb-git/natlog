#include "record.ih"

namespace {
    unordered_map<size_t, char const *> flagName =
    {
        { Record::FIN,  "FIN "  }, 
        { Record::SYN,  "SYN "  }, 
        { Record::RST,  "RST "  }, 
        { Record::PUSH, "PUSH " }, 
        { Record::ACK,  "ACK "  }, 
        { Record::URG,  "URG "  }, 
        { Record::ECE,  "ECE "  }, 
        { Record::CWR,  "CWR "  }, 
    };
}

#include <iostream>

string Record::showFlags() const
{
    string ret;

    for (size_t flag = 1; flag & Record::TCP_Flags_MASK; flag <<= 1)
    {
        if (size_t key = flag & d_flags)
            ret += flagName[key];
    }

    if (ret.length())
        ret.pop_back();

    return ret;
}
