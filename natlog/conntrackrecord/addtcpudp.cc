#include "conntrackrecord.ih"

void ConntrackRecord::addTcpudp(std::string const &key, Pattern const &pat)
{
    *firstFree() = new Record 
                    {
                        key, 
                        pat[ idx(CTtcpudp::TIME1) ], 
                        pat[ idx(CTtcpudp::TIME2) ], 
                        pat[ idx(CTtcpudp::PROTOCOL) ], 
                        pat[ idx(CTtcpudp::SRC) ], 
                        pat[ idx(CTtcpudp::DST) ], 
                        pat[ idx(CTtcpudp::SPORT) ], 
                        pat[ idx(CTtcpudp::DPORT) ], 
                        pat[ idx(CTtcpudp::NATSRC) ], 
                        pat[ idx(CTtcpudp::NATPORT) ],
                        0, 0
//                        sizes ? 
//                            stoul(pat[ idx(CTtcpudp::SENTBYTES) ]) : 0,
//                        sizes ? 
//                            stoul(pat[ idx(CTtcpudp::RECVDBYTES) ]) : 0,
                    };
}
