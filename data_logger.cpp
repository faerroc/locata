#include "data_logger.h"

using namespace std;

std::string m_filename;

bool DataLogger::Write(const std::string& line)
{
    std::ofstream file;
    file.open(m_filename,std::ios::out | std::ios::app);
    if (file.fail())
    {
        return false;
    }   
    file << line << endl;
    file.close();
    return true;
}

void DataLogger::SetFilename(const std::string& filename)
{
    m_filename = filename;
}