#include "tcp.ih"

namespace {
    size_t a_tcpSize = 50;
}

void TCP::cleanupHook()
{
    keyMapCleanup(d_keyMap);

    maybeSizeLog(&a_tcpSize, d_keyMap.size(), "TCP");
}
