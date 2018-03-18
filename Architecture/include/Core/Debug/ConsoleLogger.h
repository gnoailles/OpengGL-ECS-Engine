#pragma once
#include <Core/Debug/LogSink.h>

namespace Core
{
	namespace Debug
	{
		class ConsoleLogger : public LogSink
		{
		public:
			ConsoleLogger();
			~ConsoleLogger();
			void LogLine(const std::string& p_message,
						 const char* p_function,
						 const char* p_file,
						 const int p_line,
			             const LogLevel p_level) override;
		};
	}
}
