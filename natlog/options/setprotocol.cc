#include "options.ih"

string Options::setProtocol()
{
    string ret;

    string spec;
    if (not d_arg.option(&spec, "protocol"))
        ret = " -p tcp";
    else if (spec != "all")
    {
        ret = protocol("icmp", spec);
        ret += protocol("tcp", spec);
        ret += protocol("udp", spec);

        if (not spec.empty())
            wmsg << "Protocol specification `" << spec << "' not supported" <<
                                                                    endl;
    }
    return ret;
}
