#ifndef INCLUDED_PRODUCER_
#define INCLUDED_PRODUCER_

#include <utility>

class Storage;

class Producer
{
    public:
        virtual ~Producer();

        static void process(Producer *producer, Storage &storage);

//        template <typename Derived, typename ...Params>
//        static Producer *alloc(Params &&...params);         

    private:
        virtual void run() = 0;
};
        
//// static
//template <typename Derived, typename ...Params>
//inline Producer *Producer::alloc(Params &&...params)
//{
//    return new Derived{ std::forward<Params>(params)... };
//}

#endif
