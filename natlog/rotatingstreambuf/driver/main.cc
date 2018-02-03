#include <iostream>
#include <string>
#include <chrono>
#include <thread>

#include "../../rotatingstream/rotatingstream.h"

using namespace std;

int main()
{
    RotatingStream out{1};

    out.open("out");

    for (size_t idx = 0; idx != 35; ++idx)
    {
        cout << idx << " hello world\n";
        out << idx << " hello world" << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }

}
