#ifndef __GAME_UTILS_LOGGER_H__
#define __GAME_UTILS_LOGGER_H__

#include <memory>
#include <string>
#include <sstream>

namespace game::utils {

struct ILogger
{
	virtual void Log(const std::string& msg) = 0;
};

std::shared_ptr<ILogger> DefaultLoggerInstance();

} // namespace game::utils

#define LOG(msg) { \
    std::stringstream ss; \
    ss << msg << '\n'; \
    game::utils::DefaultLoggerInstance()->Log(ss.str()); \
}

#endif // __GAME_UTILS_LOGGER_H__
