#pragma once

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#define MAX_STR_LEN       255

struct UtilTime_t {
    uint64_t sec; 
    uint32_t msec;
};

class Utils
{
public:
    Utils();

    static int ReadFileInt(std::string filename);
    static std::string GetStdoutFromCommand(std::string cmd);
    static bool FileExists(const char *fileName);    
    static bool TimeGet(UtilTime_t * time);
    static bool TimeGetElapsed(UtilTime_t * start, uint32_t interval_ms);
    
private:
};
