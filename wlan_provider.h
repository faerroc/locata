#pragma once

#include <iostream> 
#include <mutex>
#include <thread>
#include <queue>
#include <condition_variable>
#include <atomic>

#include "wifi_scan.h"
#include "location.h"

#define BSS_INFOS         10
#define SCAN_INTERVAL_SEC 30

class WlanProvider
{
public:
    WlanProvider();

    static void run();

    static void scan_loop();

    static void setESSID(const std::string& _essid);
    static void setIFACE(const std::string& _iface);

private:
    
};


