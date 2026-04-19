#include "Time.h"

#include <chrono>
#include <sstream>
#include <iomanip>
#include <thread>

void Core::Time::sleep(float seconds) {
    using namespace std::chrono_literals;

    std::this_thread::sleep_for(seconds * 1s);
}

std::string Core::Time::getTimeInfo(const std::string& format) {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), format.c_str());
    return ss.str();
}

