#include "connectionsconsumer.ih"

unordered_map<Record::Protocol, void (ConnectionsConsumer::*)(Record &)> 
ConnectionsConsumer::s_handler = 
{
    { Record::ICMP,             &ConnectionsConsumer::icmp }, 
    { Record::TCP,              &ConnectionsConsumer::tcp }, 
    { Record::UDP,              &ConnectionsConsumer::udp }, 
};

char const *ConnectionsConsumer::s_logType[]
{
    "",
    " (INCOMPLETE)",
    " (EOP)"
};
