#include "pcap.ih"

// static
string Pcap::pcapFilterExpr() 
{
    istringstream in(Options::instance().protocols());

    string ret;
    string protocol;

    while (in >> protocol)
        ret += protocol + " or ";

    ret.resize(ret.size() - 4;
    return ret;                     // return protocol or multiple 
}                                   // or-separated protocols
