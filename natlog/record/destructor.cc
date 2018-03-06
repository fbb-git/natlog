#include "record.ih"

Record::~Record()
{
    --s_count;

//CERR << s_count-- << '\n';
}
