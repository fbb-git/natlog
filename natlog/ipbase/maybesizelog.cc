#include "ipbase.ih"

void IPbase::maybeSizeLog(size_t *lastSize, size_t keyMapSize, 
                          char const *label)
{
                                                    // debug and #entries have
                                                    // significantly changed
    if (g_debug.good() && abs(static_cast<int>(size() - *lastSize)) > 50)  
        g_debug << 
                label << " # entries: " << (*lastSize = size()) << 
                        ", keyMap size: " <<keyMapSize <<
                        ", # records: " << Record::count() << endl;
}
