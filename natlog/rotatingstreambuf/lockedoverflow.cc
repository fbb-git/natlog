#include "rotatingstreambuf.ih"

int RotatingStreambuf::lockedOverflow(int ch)
{
    return d_out.rdbuf()->sputc(ch);
}
