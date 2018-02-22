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

    KeyMap d_keyMap;

    static void (TCP::*s_tcpIn[]) (Record *);

    public:
        TCP(std::ostream &stdMsg, std::ostream &logDataStream);

    private:
        void inDev(Record *next)    override;

        void sent(Record *next);                    // called from inDev,
                                                    // override not needed

        void received(Record *next) override;       // but not called via
                                                    // IPbase, as inDev is
                                                    // overridden
        void outDev(Record const *next) override;

        TCP_type inType(Record const *record);

        void fin(Record *next);
        void ignore(Record *next);
        void syn(Record *next);
};
        
#endif

