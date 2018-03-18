#pragma once
#include <string>
#include <Core/Debug/LogLevel.h>

namespace Core
{
	namespace Debug
	{
		class LogSink
		{
		public:
			virtual ~LogSink(){};

			virtual void LogLine(const std::string& p_message,
				const char* p_function,
				const char* p_file,
				int p_line,
				LogLevel p_level) = 0;
		};
	}
}


