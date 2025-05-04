#pragma once
#include <ctime>
#include <iostream>
#include <mutex>
#include <atomic>

namespace GLog {
enum LOG_LEVEL { LOG_ERROR, LOG_WARNING, LOG_DEBUG, LOG_TRACE };

static bool SET_LOG_LEVEL = false;
static std::atomic<LOG_LEVEL> CURRENT_LOG_LEVEL;
static std::mutex LOG_MUTEX;

inline void SetLogLevel(LOG_LEVEL _level) {
  SET_LOG_LEVEL = true;
  CURRENT_LOG_LEVEL = _level;
}

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
  if (!SET_LOG_LEVEL) {
    SetLogLevel(LOG_LEVEL::LOG_ERROR);
  }

  std::string output;

  if (_level <= CURRENT_LOG_LEVEL) {
    switch (_level) {
      case LOG_LEVEL::LOG_ERROR:
        output += "\x1B[1;3;31m[ERROR][" + GetTime() + "] : \x1B[0m";
        break;
      case LOG_LEVEL::LOG_WARNING:
        output += "\x1B[1;3;35m[WARNING][" + GetTime() + "] : \x1B[0m";
        break;
      case LOG_LEVEL::LOG_DEBUG:
        output += "\x1B[1;3;32m[DEBUG][" + GetTime() + "] : \x1B[0m";
        break;
      case LOG_LEVEL::LOG_TRACE:
        output += "\x1B[1;3;34m[TRACE][" + GetTime() + "] : \x1B[0m";
        break;
      default:
        output += "[UNKOWN][" + GetTime() + "] : ";
        break;
    }

    output += _message;

    LOG_MUTEX.lock();
    if (_level < LOG_LEVEL::LOG_WARNING) {
      std::cout << output << std::endl;
    } else {
      std::cerr << output << std::endl;
    }
    LOG_MUTEX.unlock();
  }
}
} // namespace Log
