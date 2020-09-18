#include "publisher.h"

using namespace std;

extern std::queue<Location> m_data;
extern std::mutex m;
extern std::condition_variable cv;

Publisher::Publisher()
{}

void Publisher::run()
{
    Location item;
    while(1)
    {
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk, [] () { return !m_data.empty(); });
        item = m_data.front();        
        m_data.pop();
        MqttDriver::publish(item);
        DataLogger::Write(item.getLocationBuffer());
    }
}
