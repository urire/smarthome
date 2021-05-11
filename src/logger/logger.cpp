#include "logger.hpp"       // smart_home::Logger

namespace smart_home {

Logger::Logger(const std::string& a_name)
: m_name(a_name)
, m_message()
{  
}

const std::string& Logger::Name() const {
    return m_name;
}

std::string Logger::Message() const {
    return m_message.str();
}

void Logger::Log(const std::string& a_msgToLog) {
    m_message << a_msgToLog << "\n";
}

} // smart_home
