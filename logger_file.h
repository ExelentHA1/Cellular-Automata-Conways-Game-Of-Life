/*
AI generated logger shame :(
*/


#ifndef SIMPLE_LOGGER_H
#define SIMPLE_LOGGER_H

#include <fstream>
#include <mutex>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

enum class LogLevel { Debug, Info, Warn, Error };

class SimpleLogger {
public:
    SimpleLogger(const std::string &filename)
        : ofs(filename, std::ios::app)
    {}

    ~SimpleLogger() { if (ofs.is_open()) ofs.close(); }

    void log(LogLevel level, const std::string &msg) {
        std::lock_guard<std::mutex> lock(mtx);
        if (!ofs.is_open()) return;
        ofs << timestamp() << " [" << levelName(level) << "] " << msg << "\n";
        ofs.flush();
    }

    // convenience
    void debug(const std::string &m) { log(LogLevel::Debug, m); }
    void info (const std::string &m) { log(LogLevel::Info,  m); }
    void warn (const std::string &m) { log(LogLevel::Warn,  m); }
    void error(const std::string &m) { log(LogLevel::Error, m); }

private:
    std::ofstream ofs;
    std::mutex mtx;

    static std::string levelName(LogLevel l) {
        switch (l) {
            case LogLevel::Debug: return "DEBUG";
            case LogLevel::Info:  return "INFO";
            case LogLevel::Warn:  return "WARN";
            case LogLevel::Error: return "ERROR";
        }
        return "UNK";
    }

    static std::string timestamp() {
        using namespace std::chrono;
        auto now = system_clock::now();
        auto tt = system_clock::to_time_t(now);
        auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

        std::tm tm;
#ifdef _WIN32
        localtime_s(&tm, &tt);
#else
        localtime_r(&tt, &tm);
#endif
        std::ostringstream ss;
        ss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S")
           << '.' << std::setfill('0') << std::setw(3) << ms.count();
        return ss.str();
    }
};

#endif // SIMPLE_LOGGER_H
