#include "GLog/Log.hpp"
#include <iostream>
#include <mutex>
#include <atomic>
#include <ctime>

namespace GLog {

static std::string LOG_PREFIX;
static bool SET_LOG_LEVEL = false;
static std::atomic<LOG_LEVEL> CURRENT_LOG_LEVEL;
static std::mutex LOG_MUTEX;

static inline std::string GetTime() {
  char buffer[32];
  time_t time = std::time(nullptr);

  if (!std::strftime(buffer, sizeof(buffer), "%H:%M:%S",
                     std::localtime(&time))) {
    return "";
  } else {
    return buffer;
  }
};

void SetLogPrefix(const std::string &_prefix) {
  LOG_MUTEX.lock();
  LOG_PREFIX = _prefix;
  LOG_MUTEX.unlock();
}

void SetLogLevel(LOG_LEVEL _level) {
  LOG_MUTEX.lock();
  SET_LOG_LEVEL = true;
  CURRENT_LOG_LEVEL = _level;
  LOG_MUTEX.unlock();
}

void Log(LOG_LEVEL _level, const std::string &_message) {
  if (!SET_LOG_LEVEL) {
    SetLogLevel(LOG_LEVEL::LOG_ERROR);
  }

  LOG_MUTEX.lock();
  std::string output = LOG_PREFIX;

  if (_level <= CURRENT_LOG_LEVEL) {
    switch (_level) {
    case LOG_LEVEL::LOG_PRINT:
      output.clear();
      break;
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
    std::cout << output << std::endl;
  }

  LOG_MUTEX.unlock();
}
} // namespace GLog
