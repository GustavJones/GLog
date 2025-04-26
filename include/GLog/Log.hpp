#pragma once
#include <ctime>
#include <iostream>
#include <mutex>
#include <atomic>

namespace GLog {
enum LOG_LEVEL { LOG_ERROR, LOG_WARNING, LOG_DEBUG, LOG_TRACE };

static const std::atomic<LOG_LEVEL> CURRENT_LOG_LEVEL = LOG_DEBUG;
static std::mutex LogMutex; 

static inline std::string GetTime() {
  char buffer[32];
  time_t time = std::time(nullptr);

  if (!std::strftime(buffer, sizeof(buffer), "%H:%M:%S", std::localtime(&time))) {
    return "";
  }
  else {
    return buffer;
  }
};

inline void Log(LOG_LEVEL _level, const std::string &_message) {
  std::string output;

  if (_level <= CURRENT_LOG_LEVEL) {
    switch (_level) {
      case LOG_LEVEL::LOG_ERROR:
        output += "[ERROR][" + GetTime() + "] : ";
        break;
      case LOG_LEVEL::LOG_WARNING:
        output += "[WARNING][" + GetTime() + "] : ";
        break;
      case LOG_LEVEL::LOG_DEBUG:
        output += "[DEBUG][" + GetTime() + "] : ";
        break;
      case LOG_LEVEL::LOG_TRACE:
        output += "[TRACE][" + GetTime() + "] : ";
        break;
      default:
        output += "[UNKOWN][" + GetTime() + "] : ";
        break;
    }

    output += _message;

    LogMutex.lock();
    if (_level < LOG_LEVEL::LOG_WARNING) {
      std::cout << output << std::endl;
    } else {
      std::cerr << output << std::endl;
    }
    LogMutex.unlock();
  }
}
} // namespace Log
