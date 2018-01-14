#include "options.ih"

bool Options::hasProtocol(std::string const &name) const
{
    auto iter = s_name2protocol.find(name); 

    return iter != s_name2protocol.end() and 
                d_protocols.find(iter->second) != d_protocols.end();
}
