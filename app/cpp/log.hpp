#pragma

/* Usage:
 *    #include "log.hpp"
 *
 *    Log->info("...");
 *    Log->warn("...");
 */

#include <spdlog/spdlog.h>
#include <spdlog/sinks/android_sink.h>
#define TAG "{{crate_name}}"

class AndroidLog
{
public:
  static std::shared_ptr<spdlog::logger> Instance() {
    static std::shared_ptr<spdlog::logger> m_logger = spdlog::android_logger_mt("android", TAG);
    m_logger->set_pattern("%v");
    return m_logger;
  }
private:
  AndroidLog() {}
  virtual ~AndroidLog() {}
};

#define Log AndroidLog::Instance()

/* 
 * Another method uses `set_default_logger` to spdlog at first line in main entry. 
 * It can keep using spdlog::info, spdlog::debug command rather than Log->info
 *
 * 		std::shared_ptr<spdlog::logger> android_logger = spdlog::android_logger_mt("android", "TAG");
 * 		spdlog::set_pattern("%v");
 * 		spdlog::set_default_logger(android_logger);
*/
