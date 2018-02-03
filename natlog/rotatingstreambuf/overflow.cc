#include "rotatingstreambuf.ih"

int RotatingStreambuf::overflow(int ch)
{
    return (this->*d_overflow)(ch);
}
