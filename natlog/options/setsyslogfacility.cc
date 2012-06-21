#include "options.ih"

void Options::setSyslogFacility()
{
    string option;
    if (not d_arg.option(&option, "syslog-facility"))
        d_syslogFacility = s_syslogFacilities.find(s_defaultSyslogFacility);
    else
    {
        std::unordered_map<std::string, FBB::Facility>::const_iterator 
            facility = s_syslogFacilities.find(option);

        if (facility != s_syslogFacilities.end())
            d_syslogFacility == facility;
        else
            d_syslogFacilityError = option;
    }            
}
