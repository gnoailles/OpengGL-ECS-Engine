#pragma once
#include <string>

#define LOG(Logger_, Message_)                  \
  Logger_(                                      \
    static_cast<std::ostringstream&>(           \
      std::ostringstream().flush() << Message_  \
    ).str(),                                    \
    __FUNCTION__,                               \
    __FILE__,                                   \
    __LINE__                                    \
  );


#include <Core/Debug/ConsoleLogger.h>
#include <Core/Debug/LogSink.h>
#include "LogLevel.h"
#include "FileLogger.h"

namespace Core
{
	namespace Debug
	{

		class Log
		{

		private:
			LogLevel m_level;
			LogSink& m_sink;
			static ConsoleLogger console;
			static FileLogger logFile;

		public:
			Log(const LogLevel p_level, LogSink& p_sink);

			void operator()(const std::string& p_message,
				const char* p_function,
				const char* p_file,
				const int p_line) const;


			static Log& Info();
			static Log& Debug();
			static Log& Warning();
			static Log& Error();
			static Log& Fatal();

		};

	}
}
