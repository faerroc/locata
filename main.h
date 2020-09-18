#pragma once

#include <iostream> 
#include <mutex>
#include <thread>
#include <queue>
#include <condition_variable>
#include <chrono>
#include <csignal>

#include "publisher.h"
#include "wlan_provider.h"
#include "mqtt_driver.h"
#include "location.h"
#include "config.h"
#include "log.h"
#include "data_logger.h"

#define VERSION_CODE   "1.0.0"
#define MODULE_NAME    "locata"
#define MODULE_VERSION "Ver. " VERSION_CODE " " __DATE__ " " __TIME__