#pragma once

#include <fstream>
#include <iostream>
#include <string>

class DataLogger
{
public:
    DataLogger();

    static bool Write(const std::string& line);

    static void SetFilename(const std::string& filename);
    
private:    
};
