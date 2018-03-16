#include "natfork.ih"

// static
Producer *NatFork::allocProducer(Options::Mode mode,
                                 ostream &stdMsg, Storage &storage)
{
    void *handle = dlopen("libnatlog.so", RTLD_LAZY);
    if (handle == 0)
        throw Exception{} << "can't open library libnatlog.so: " << dlerror();
                        
    dlerror();              // reset any errors

                                        // retrieve the function fm the lib
    Producer *(*allocFun)(ostream &stdMsg, Storage &storage) = 
        reinterpret_cast<decltype(allocFun)>( 
            dlsym(handle, s_producerAlloc[mode]) );

    if (char const *dlsym_error = dlerror())    // Exception on failure
        throw Exception{} << "can't load function `" << 
                             s_producerAlloc[mode] << ": " << dlsym_error;

    Producer *ret = (*allocFun)(stdMsg, storage);   // create the producer

    dlclose(handle);                            // library use completed
    
    return ret;
}
