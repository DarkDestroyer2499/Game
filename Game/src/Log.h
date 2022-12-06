#ifndef LOG
#define LOG

#include <iostream>
#include <string.h>
#include <ctime>

#define DEBUG 1

#define ERROR "\033[1;31mERRR\033[0m"
#define INFO "INFO"
#define WARNING "\033[1;33mWARNING\033[0m"
#define SUCCESS "\033[1;32mSUCCESS\033[0m"

std::string GetLocalTime()
{
    struct tm m_timeInfo;
    time_t t;
    time(&t);
    localtime_s(&m_timeInfo, &t);
    std::string localTime;

    if (m_timeInfo.tm_hour < 10)
        localTime += '0' + std::to_string(m_timeInfo.tm_hour);
    else
        localTime += std::to_string(m_timeInfo.tm_hour);

    localTime += ':';

    if (m_timeInfo.tm_min < 10)
        localTime += '0' + std::to_string(m_timeInfo.tm_min);
    else
        localTime += std::to_string(m_timeInfo.tm_min);

    localTime += ':';

    if (m_timeInfo.tm_sec < 10)
        localTime += '0' + std::to_string(m_timeInfo.tm_sec);
    else
        localTime += std::to_string(m_timeInfo.tm_sec);

    return localTime;
}


#define __PRETTY_FILE_NAME__ (std::string(__FILE__).substr(std::string(__FILE__).find_last_of("/\\") + 1))

#if DEBUG == 1
#define Log(severity) std::cout<< "\n[" << severity << "][" << GetLocalTime()<< "][" << __PRETTY_FILE_NAME__ << "][" << __func__ << "][" << __LINE__ << "]: "
#else
#define Log(severity, msg)
#endif // DEBUG

#endif // !LOG