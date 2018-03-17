#include "ipbase.ih"

void IPbase::keyMapCleanup(KeyMap &keyMap)
{
    vector<size_t> remove;

        // see ipbase.h for details at KeyMapStruct
    for (auto &value: keyMap)
    {
        if (find(value.second.key) == end())    // key doesn't point to an
        {                                       //  existing Record
            if (value.second.expired)           // Expired, so 
                remove.push_back(value.first);  //  remove the keyMap's entry
            else                                // otherwise
                value.second.expired = true;    //  remove it at the next 
        }                                       // cleanup (or at FIN)
    }

    for (size_t key: remove)
        keyMap.erase(keyMap.find(key));
}
