//#include "pcapfilter.ih"
//
//size_t PcapFilter::find(size_t id)
//{
//    auto iter = find_if(d_connections.begin(), d_connections.end(), 
//                    [&](PcapRecord const *record)
//                    {
//                        return record->id() == id;
//                    }
//                );
//
//    return iter == d_connections.end() ? 
//                numeric_limits<size_t>::max()
//            :
//                iter - d_connections.begin();
//}
//
//
