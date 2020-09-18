#include "location.h"

Location::Location()
{
    m_utc       = 0;
    m_essid     = "";
    m_bssid     = "";
    m_ssid      = "";
    m_rssi      = 0;
    m_frequency = 0;
    m_type      = 0;
    m_status    = 0;
    m_location  = "";
}

Location::~Location()
{

}

std::string& Location::getLocationBuffer()
{
    char buffer[MAX_BUFFER_LEN];

    snprintf(buffer, MAX_BUFFER_LEN, "%lu ; %s ; %s ; %s ; %d ; %d ; %d ; %d", 
                                       m_utc,m_essid.c_str(),m_bssid.c_str(),m_ssid.c_str(),
                                       m_rssi,m_frequency,m_type,m_status);

    m_location = "";
    m_location = buffer;
    return m_location;
}
