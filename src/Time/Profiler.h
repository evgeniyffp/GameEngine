#pragma once

#include <string>
#include <unordered_map>

#include "./Timer.h"

class Profiler {
private:
    struct time_interval_t {
        float start;
        float end;
    };

    Timer timer;
    std::unordered_map<std::string, time_interval_t> times;

public:
    void start(const std::string& name) {
        times[name].start = timer.elapsed_milliseconds();
    }
    
    void end(const std::string& name) {
        times[name].end = timer.elapsed_milliseconds();
    }

    float get(const std::string& name) const {
        const auto& it = times.find(name);

        if (it == times.end())
            return 0.f;

        auto time_interval = it->second;
        return (time_interval.end - time_interval.start) / 1000.f; // convert to second
    }
};

