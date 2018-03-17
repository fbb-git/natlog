#include "udp.ih"

namespace {
    size_t a_udpSize = 50;
}

void UDP::cleanupHook()
{
    keyMapCleanup(d_keyMap);

    maybeSizeLog(&a_udpSize, d_keyMap.size(), "UDP");
}
