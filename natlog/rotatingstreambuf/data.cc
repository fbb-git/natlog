#include "rotatingstreambuf.ih"

vector<RotatingStreambuf *> RotatingStreambuf::s_rotate;

Semaphore RotatingStreambuf::s_semaphore{ 0 };
thread RotatingStreambuf::s_rotateThread;
