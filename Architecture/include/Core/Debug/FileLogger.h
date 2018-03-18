#pragma once
#include "LogSink.h"
#include <fstream>

namespace Core
{
	namespace Debug
	{
		class FileLogger : public LogSink
		{
		private:
			std::fstream m_logfile;
		public:
			FileLogger(const char* p_filePath);
			FileLogger(FileLogger&& p_fileLogger) noexcept;
			~FileLogger();
			void LogLine(const std::string& p_message, const char* p_function, const char* p_file, const int p_line,
				const LogLevel p_level) override;
		};
	}
}
