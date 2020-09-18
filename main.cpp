#include "main.h"

using namespace std;

std::queue<Location> m_data;
std::mutex m;
std::condition_variable cv;

//==============================================================================================
//= Handlers
//==============================================================================================

void my_terminate_handler(void) 
{
    Log::log(Log::WARN, "Terminate handler called !\n");
    exit(EXIT_SUCCESS);
}

void out_of_memory()
{
	Log::log(Log::ERROR, "ERROR - Out of Memory !\n");
    exit(EXIT_FAILURE); 
}

//==============================================================================================
//= Signal Handling
//==============================================================================================

void sig_handler(int signo)
{
    switch (signo) 
    {
    case SIGUSR1:
        Log::setLogLevel(Log::ALL);
        break;
    case SIGUSR2:
        Log::setLogLevel(Log::NONE);
        break;
	case SIGKILL:
		exit(EXIT_SUCCESS);
		break;	
    default:
        break;
    }
}

//==============================================================================================
//= Main
//==============================================================================================

int main(int argc, char **argv)
{
	Log::setLogLevel(Log::ALL);

    signal(SIGUSR1, sig_handler);
    signal(SIGUSR2, sig_handler);    

	std::set_terminate  (my_terminate_handler);
	std::set_new_handler(out_of_memory);

    Config::Parse("locata.conf");

    MqttDriver::initialize();

    std::string my_wlan_mac = Utils::GetStdoutFromCommand("ifconfig wlan0 | grep HWaddr | awk -F ' ' '{print $5}'");
    std::string iface       = Config::GetByKey("IFACE");
    std::string data_file   = Config::GetByKey("DATAFILE");

    WlanProvider::setESSID(my_wlan_mac);
    WlanProvider::setIFACE(iface);

    DataLogger::SetFilename(data_file);

    std::thread p_task(WlanProvider::scan_loop);
    std::thread c_task(Publisher::run);

    p_task.join();
    c_task.join();

    MqttDriver::close();

    Log::log(Log::WARN,"Finishing module\n");   

    return EXIT_SUCCESS;
}
