#include "storage.ih"

Record *Storage::fetch()
{
    lock_guard<mutex> lg{ d_mutex };

        // if this throws, nothing has been removed. 
    d_record = d_queue.front();

        // once we reach this point we own the queue's front element and it
        // can be removed

    d_queue.pop();

    return d_record;
}
