#pragma once

#include "utils.h"

#include <string>

#define MAX_BUFFER_LEN 512

class Location {
    private:
        unsigned long m_utc;
        std::string m_essid;
        std::string m_bssid;
        std::string m_ssid;
        int m_rssi;
        int m_frequency;
        int m_type;
        int m_status;
        std::string m_location;

    public:
        Location();
        ~Location();

        void setUtc(const unsigned long& _utc){m_utc = _utc;}
        unsigned long& getUtc() {return m_utc;}

        void setESSID(const std::string& _essid){m_essid = _essid;}
        std::string& getESSID() {return m_essid;}

        void setBSSID(const std::string& _bssid){m_bssid = _bssid;}
        std::string& getBSSID() {return m_bssid;}

        void setSSID(const std::string& _ssid){m_ssid = _ssid;}
        std::string& getSSID() {return m_ssid;}  

        void setRSSI(const int& _rssi){m_rssi = _rssi;}
        int& getRSSI() {return m_rssi;}      

        void setFrequency(const int& _frequency){m_frequency = _frequency;}
        int& getFrequency() {return m_frequency;}    

        void setType(const int& _type){m_type = _type;}
        int& getType() {return m_type;}       

        void setStatus(const int& _status){m_status = _status;}
        int& getStatus() {return m_status;}  

        std::string& getLocationBuffer();                                   
};


