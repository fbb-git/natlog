#include "options.ih"

Options::Options()
:
    d_arg(ArgConfig::instance())
{
        // the config file is:
        //      - where specified at 'c',   or:
        //      - ~/.natlogrc

    string config;
    if (not d_arg.option(&config, 'c'))
        config = User().homedir() + s_defaultConfigFileName;

    if (Stat(config))
        d_arg.open(config);

    d_verbose = d_arg.option(0, "verbose");
}
