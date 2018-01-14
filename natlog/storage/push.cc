#include "storage.ih"

void Storage::push(Record &&record)
{
    d_available.wait();

    {
        lock_guard<mutex> lg{ d_mutex };
    
        d_queue.push(move(record));
    }

    d_filled.notify();
}

