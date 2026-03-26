#pragma once

#include <spdlog/spdlog.h>

namespace Log {
    enum class LogLevel {
        Debug = spdlog::level::level_enum::debug,
        Info = spdlog::level::level_enum::info,
        Warning = spdlog::level::level_enum::warn,
        Error = spdlog::level::level_enum::err,
        Critical = spdlog::level::level_enum::critical,
    };

    static void init() {
        spdlog::set_level(spdlog::level::debug);
    }
    
    template <typename... Args>
    void log(LogLevel log_level, Args&&... args) {
        spdlog::log(static_cast<spdlog::level::level_enum>(log_level), std::forward<Args>(args)...);
    }

    template <typename... Args>
    void debug(Args&&... args) {
        log(LogLevel::Debug, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void info(Args&&... args) {
        log(LogLevel::Info, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void warning(Args&&... args) {
        log(LogLevel::Warning, std::forward<Args>(args)...);
    }
    
    template <typename... Args>
    void error(Args&&... args) {
        log(LogLevel::Error, std::forward<Args>(args)...);
    }
    
    template <typename... Args>
    void critical(Args&&... args) {
        log(LogLevel::Critical, std::forward<Args>(args)...);
    }
}
