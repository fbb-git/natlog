#include <iostream>
#include <string>

#include <bobcat/argconfig>

#include "../tcpdumpproducer.h"

#include "../../storage/storage.h"

using namespace std;
using namespace FBB;


// start as         tmp/bin/binary tcpdump icmp /tmp/br0 /tmp/eth1 

namespace   // the anonymous namespace can be used here
{
    Arg::LongOption longOptions[] =
    {
        Arg::LongOption("config", 'c'),

        Arg::LongOption("conntrack-command", Arg::Required),
        Arg::LongOption("conntrack-device", Arg::Required),
        Arg::LongOption("conntrack-restart", Arg::Required),
        Arg::LongOption("help", 'h'),
        Arg::LongOption("no-daemon", Arg::None),
        Arg::LongOption("no-syslog", Arg::None),
        Arg::LongOption("pid-file", 'p'),
        Arg::LongOption("protocol", 'P'),
        Arg::LongOption("stdout", 's'),
        Arg::LongOption("syslog-facility", Arg::Required),
        Arg::LongOption("syslog-priority", Arg::Required),
        Arg::LongOption("syslog-tag", Arg::Required),
        Arg::LongOption("time", 't'),
        Arg::LongOption("verbose", 'V'),
        Arg::LongOption("version", 'v'),
        Arg::LongOption("warn", 'w'),
    };

    auto longEnd = longOptions + size(longOptions);
}

// start as         tmp/bin/binary tcpdump icmp /tmp/br0 /tmp/eth1 


int main(int argc, char **argv)
{
    ArgConfig::initialize("c:hp:P:st:vVw", 
                        longOptions, longEnd, argc, argv);

    TcpdumpProducer producer{ cerr };

    Storage storage;

    producer.run(storage);
}
