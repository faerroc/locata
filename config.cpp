#include "config.h"

using namespace std;

std::map<string, string> m_config;

bool Config::Parse(const string& file)
{
    ifstream filestream(file);

    if ( filestream )
    {
        string line;
        while(getline(filestream, line))
        {
            istringstream is_line(line);
            string key;
            if(getline(is_line, key, '='))
            {
                string value;
                if(getline(is_line, value))
                {
                    m_config[key] = value;
                }                    
            }
        }
    }

    filestream.close();
    return true;
}

string Config::GetByKey(const string& key)
{
    return m_config[key];
}