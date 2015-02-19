#include "options.ih"

string Options::setProtocol()
{
    string ret;

    string spec;
    if (not d_arg.option(&spec, "protocol"))
    {
        ret = " -p tcp";
        d_conntrackProtocol = "tcp";
    }
    else if (spec == "all")
        d_conntrackProtocol = "tcp udp icmp";
    else
    {
        ret = protocol("icmp", spec);
        ret += protocol("tcp", spec);
        ret += protocol("udp", spec);

        if (d_conntrackProtocol.length() > 4)
            ret.erase();

        if (not spec.empty())
            wmsg << "Protocol specification `" << spec << "' not supported" <<
                                                                    endl;
    }
    return ret;
}







