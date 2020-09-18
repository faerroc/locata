#pragma once

#include <map>
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

class Config
{
public:
    Config();

    static bool Parse(const std::string& file);

    static std::string GetByKey(const std::string& key);
    
private:
    
};
