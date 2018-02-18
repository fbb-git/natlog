#ifndef INCLUDED_STORAGE_
#define INCLUDED_STORAGE_

#include <queue>

#include <bobcat/semaphore>

class Record;

class Storage
{
    enum 
    {
        AVAIL = 1000
    };

    FBB::Semaphore d_available{ AVAIL };
    FBB::Semaphore d_filled{ 0 };

    Record *d_record;                       // retrieved from the queue

    std::mutex d_mutex;    
    std::queue<Record *> d_queue;
    bool d_empty = false;                   // indicates no more data will
                                            // arrive 
    public:
        Storage() = default;
        Storage(Storage const &) = delete;

        void consumeWait();                 // i
        void produceNotify();               // i
        void push(Record *src);
        Record *fetch();                    // fetch the next record
        size_t size() const;                // i

        bool empty() const;                 // i
        void setEmpty();                    // i - sets d_empty to true
};

inline bool Storage::empty() const
{
    return d_empty && d_queue.empty();
}

inline void Storage::setEmpty()         
{
    d_empty = true;
    d_filled.notify();
}

inline size_t Storage::size() const
{
    return d_queue.size();
}
        
inline void Storage::consumeWait()
{
    d_filled.wait();
}

inline void Storage::produceNotify()
{
    d_available.notify();
}

#endif

