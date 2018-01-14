#include "options.ih"

void Options::setConntrack()
{
    if (not d_arg.option(&d_conntrackCommand, "conntrack-device"))
        d_conntrackDevice = s_defaultConntrackDevice;

    if (not d_arg.option(&d_conntrackCommand, "conntrack-command"))
        d_conntrackCommand = s_defaultConntrackCommand;

    d_conntrackCommand +=
            (
                d_protocols.size() == 1 ? 
                    " -p " + 
                        s_protocol2name.find(*d_protocols.begin())->second
                :
                    ""s
            )
        + s_defaultConntrackArgs;

    string value;
    if (d_arg.option(&value, "conntrack-restart"))
        d_conntrackRestart = stoul(value);
}
