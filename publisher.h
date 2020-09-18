#pragma once

#include <iostream> 
#include <mutex>
#include <thread>
#include <queue>
#include <condition_variable>

#include "mqtt_driver.h"
#include "location.h"
#include "data_logger.h"

class Publisher
{
public:
    Publisher();

    static void run();

private:
};


