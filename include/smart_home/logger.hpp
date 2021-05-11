#ifndef SABATO_LOGGER_HPP
#define SABATO_LOGGER_HPP

#include <string>       // std::string
#include <sstream>      // std::stringstream

namespace smart_home {

class Logger {
public:
    // Logger() = delete;
    // Logger(const Logger&) = default;
    // Logger& operator=(const Logger&) = default;
    // ~Logger() = default;

    Logger(const std::string& a_name);

    const std::string& Name() const;
    std::string Message() const;

    void Log(const std::string& a_msgToLog);

private:
    std::string m_name;
    std::stringstream m_message;

};

} // smart_home

#endif  // SABATO_LOGGER_HPP