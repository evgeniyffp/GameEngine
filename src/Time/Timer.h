#pragma once

#include <chrono>

class Timer {
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
    using Real = long double;

public:
  Timer() {
    restart();
  }

  auto time_now() const {
    return std::chrono::high_resolution_clock::now();
  }

  void restart() {
    start_time = time_now();
  }

  Real elapsed_nanoseconds() const {
    return std::chrono::duration<Real, std::nano>(time_now() - start_time).count();
  }

  Real elapsed_microseconds() const {
    return std::chrono::duration<Real, std::micro>(time_now() - start_time).count();
  }

  Real elapsed_milliseconds() const {
    return std::chrono::duration<Real, std::milli>(time_now() - start_time).count();
  }

  Real elapsed_seconds() const {
    return std::chrono::duration<Real>(time_now() - start_time).count();
  }
};

