#include "options.ih"

string Options::protocolNames() const
{
    string ret;

    for (Protocol protocol: protocolSet())
        (ret += protocolName(protocol)) += " or ";

    ret.resize(ret.length() - 4);         // remove final ' or '

    return ret;
}
