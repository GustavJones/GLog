#include "GLog/Log.hpp"

int main (int argc, char *argv[]) {
  GLog::SetLogLevel(GLog::LOG_TRACE);
  GLog::SetLogPrefix("[Test]");
  GLog::Log(GLog::LOG_PRINT, "This is a print test");
  GLog::Log(GLog::LOG_ERROR, "This is an error test");
  GLog::Log(GLog::LOG_WARNING, "This is a warning test");
  GLog::Log(GLog::LOG_DEBUG, "This is a debug test");
  GLog::Log(GLog::LOG_TRACE, "This is a trace test");
  return 0;
}
