#include "options.ih"

void Options::setSyslogPriority()
{
    string option;
    if (not d_arg.option(&option, "syslog-priority"))
        d_syslogPriority = s_syslogPriorities.find(s_defaultSyslogPriority);
    else
    {
        std::unordered_map<std::string, FBB::Priority>::const_iterator 
            priority = s_syslogPriorities.find(option);

        if (priority != s_syslogPriorities.end())
            d_syslogPriority = priority;
        else
            d_syslogPriorityError = option;
    }            
}

// "Syslog priority `" << option << "' not supported. "
//                    "(see the man-page)" << endl;
