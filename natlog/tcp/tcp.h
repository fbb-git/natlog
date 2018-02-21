#ifndef INCLUDED_TCP_
#define INCLUDED_TCP_

#include "../ipbase/ipbase.h"

class TCP: public IPbase
{
    enum TCP_type       // see s_tcpIn and 
    {
        TCP_SYN,
        TCP_FIN,
        TCP_SENT,
        TCP_RECVD,
        TCP_IGNORE
    };

    static void (TCP::*s_tcpIn[]) (Record *);

    public:
        TCP(std::ostream &stdMsg, std::ostream &logDataStream);

    private:
        void inDev(Record *next)        override;
        void outDev(Record const *next) override;

        TCP_type inType(Record *record);

        void fin(Record *next);
        void ignore(Record *next);
        void received(Record *next);
        void sent(Record *next);
        void syn(Record *next);

};
        
#endif
