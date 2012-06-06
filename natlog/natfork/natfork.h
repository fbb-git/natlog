#ifndef INCLUDED_NATFORK_
#define INCLUDED_NATFORK_

#include <bobcat/fork>

class NatFork: public FBB::Fork
{
    public:
        NatFork();

        void run();

    private:
        virtual void parentProcess() override;
        virtual void childProcess() override;
};
        
#endif
