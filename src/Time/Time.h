#pragma once

#include <string>

namespace Core {
	class Time {
	public:
		// static double get();

		static std::string getTimeInfo(const std::string& format = "%Y-%m-%d %H:%M:%S");
	};
}

