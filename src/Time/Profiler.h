#pragma once

#include <string>
#include <unordered_map>

#include "./Timer.h"

class Profiler {
private:
    struct time_interval_t {
        float start;
        float end;

        float elapsed_seconds() const {
            return (end - start) / 1000.f; // convert to seconds
        }
    };

    using data_t = std::unordered_map<std::string, time_interval_t>;

    Timer timer;
    data_t data;

public:
    class Node;

    void start(const std::string& name) {
        data[name].start = timer.elapsed_milliseconds();
    }

    void end(const std::string& name) {
        data[name].end = timer.elapsed_milliseconds();
    }

    // return seconds
    float get(const std::string& name) const {
        const auto& it = data.find(name);

        if (it == data.end())
            return 0.f;

        auto time_interval = it->second;
        return time_interval.elapsed_seconds();
    }

    const data_t& get() const {
        return data;
    }
};

class Profiler::Node {
private:
    Profiler& profiler;
    std::string name;

public:
    Node(Profiler& profiler, std::string name)
            : profiler(profiler), name(std::move(name)) {
        profiler.start(name);
    }

    ~Node() {
        profiler.end(name);
    }
};

