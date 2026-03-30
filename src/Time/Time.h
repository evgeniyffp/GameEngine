#pragma once

#include <string>

namespace Core {
	namespace Time {
        void sleep(float seconds);

		std::string getTimeInfo(const std::string& format = "%Y-%m-%d %H:%M:%S");
	};
}

