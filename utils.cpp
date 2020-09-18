#include "utils.h"

using namespace std;

int Utils::ReadFileInt(std::string filename)
{
  FILE * pFile;
  pFile = fopen (filename.c_str(),"r");
  int ret = 0;
  if (pFile!=NULL)
  {
    fscanf (pFile, "%d", &ret);	  
    fclose (pFile);
    return ret;
  }	
  else
  {
	return 0;
  }
}

std::string Utils::GetStdoutFromCommand(std::string cmd) 
{
    string data;
    FILE * stream;
    char buffer[MAX_STR_LEN];
    cmd.append(" 2>&1");

    stream = popen(cmd.c_str(), "r");

    if (stream) 
    {
        while (!feof(stream))
        {
            if (fgets(buffer, MAX_STR_LEN, stream) != NULL) 
            {
                data.append(buffer);
            }            
        }        
        pclose(stream);
    }

    data.erase(std::remove(data.begin(), data.end(), '\n'), data.end());

    return data;
}

bool Utils::FileExists(const char *fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}

bool Utils::TimeGet(UtilTime_t * time)
{
    bool retVal = false;
    struct timeval tv;

    if(gettimeofday(&tv, NULL) == 0)
    {
        time->sec = static_cast<unsigned>(tv.tv_sec);
        time->msec = tv.tv_usec / 1000;
        retVal = true;
    }
    return retVal;
}

bool Utils::TimeGetElapsed(UtilTime_t * start, uint32_t interval_ms)
{
    UtilTime_t curr;
    TimeGet(&curr);
    return(((curr.sec - start->sec) * 1000 + curr.msec - start->msec) > interval_ms);
}
