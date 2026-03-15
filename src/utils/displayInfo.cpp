#include "./displayInfo.h"

#include <spdlog/spdlog.h>

#include <Time/Time.h>

void displayInfo(const std::string& info) {
    spdlog::info("[{}] {}", Core::Time::getTimeInfo(), info);
}

