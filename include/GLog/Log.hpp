#pragma once
#include <string>

namespace GLog {
enum LOG_LEVEL { LOG_PRINT, LOG_ERROR, LOG_WARNING, LOG_DEBUG, LOG_TRACE };
void SetLogPrefix(const std::string &_prefix);
void SetLogLevel(LOG_LEVEL _level);
void Log(LOG_LEVEL _level, const std::string &_message);
} // namespace GLog
