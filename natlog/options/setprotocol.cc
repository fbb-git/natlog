#include "options.ih"

void Options::setProtocol()
{
    string spec;

    if (not d_arg.option(&spec, 'P'))
        d_protocols.insert(TCP);

    else if (spec == "all")
        d_protocols = { TCP, UDP, ICMP };

    else
    {
        size_t pos = 0;
        size_t colon;
        while (true)
        {
            colon = spec.find(':', pos);    

            string protocol = spec.substr(pos, colon - pos);

            auto iter = s_name2protocol.find(protocol);
            if (iter == s_name2protocol.end())
                fmsg << "protocol `" << protocol << 
                            "' currently not supported" << noid;

            d_protocols.insert(iter->second);

            if (colon == string::npos)
                break;

            pos = colon + 1;
        }

        if (d_mode == CONNTRACK and pos != 0)
            fmsg << 
                "multiple protocols not supported with 'conntrack'" <<
                noid;
    }
}







