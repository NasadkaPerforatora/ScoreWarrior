#include "logger.h"
#include <iostream>

namespace game::utils {

class DefaultLogger : public ILogger
{
public:
    DefaultLogger(std::ostream& stream) noexcept
        : m_stream(stream)
    {
    }

    virtual ~DefaultLogger() = default;

    void Log(const std::string& msg) final
    {
        m_stream << msg;
    }

private:
    std::ostream& m_stream;
};

std::shared_ptr<ILogger> DefaultLoggerInstance()
{
    static auto logger{ std::make_shared<DefaultLogger>(std::cout) };
    return logger;
}

} // namespace game::utils
