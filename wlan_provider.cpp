#include "wlan_provider.h"

using namespace std;

extern std::queue<Location> m_data;
extern std::mutex m;
extern std::condition_variable cv;

std::string m_essid;
std::string m_iface;

WlanProvider::WlanProvider()
{}

void WlanProvider::setESSID(const std::string& _essid)
{
    m_essid = _essid;
}

void WlanProvider::setIFACE(const std::string& _iface)
{
    m_iface = _iface;
}

const char * bssid_to_string(const uint8_t bssid[BSSID_LENGTH], char bssid_string[BSSID_STRING_LENGTH])
{
	snprintf(bssid_string, BSSID_STRING_LENGTH, "%02x:%02x:%02x:%02x:%02x:%02x",
         bssid[0], bssid[1], bssid[2], 
         bssid[3], bssid[4], bssid[5]);
	return bssid_string;
}

void WlanProvider::scan_loop(void)
{
	struct wifi_scan *wifi=NULL;
	struct bss_info bss[BSS_INFOS];
	char mac[BSSID_STRING_LENGTH];
	int status, i;
    Location location;
    UtilTime_t _time;

	wifi=wifi_scan_init(m_iface.c_str());

	while(1)
	{
		status=wifi_scan_all(wifi, bss, BSS_INFOS);
		
		if(status<0)
        {
            perror("Unable to get scan data");
        }
		else 
        {
			for(i=0;i<status && i<BSS_INFOS;++i)
            {
				Utils::TimeGet(&_time);
				
                location.setUtc(_time.sec);
                location.setESSID(m_essid);
                location.setBSSID(bssid_to_string(bss[i].bssid, mac));
                location.setSSID(bss[i].ssid);
                location.setRSSI(bss[i].signal_mbm/100);
                location.setFrequency(bss[i].frequency);
                location.setType(0);
                location.setStatus(bss[i].status);    

                std::lock_guard<std::mutex> lg(m);
                m_data.push(location);   
                cv.notify_one(); 
            }	
        }

		std::this_thread::sleep_for(std::chrono::seconds(SCAN_INTERVAL_SEC));
	}
	
	wifi_scan_close(wifi);
}
