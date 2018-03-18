#include <Core/Debug/Log.h>
#include "Utils/Timer.h"

using namespace Core::Debug;

ConsoleLogger Log::console = ConsoleLogger();
FileLogger Log::logFile = FileLogger("logs/newLog.txt");

Log::Log(const LogLevel p_level, LogSink& p_sink): m_level(p_level), m_sink(p_sink)
{}

void Log::operator()(const std::string& p_message, const char* p_function, const char* p_file, const int p_line) const
{
	m_sink.LogLine(p_message, p_function, p_file, p_line, m_level);
}

Log& Log::Info()
{
	static Log logger(LogLevel::INFO, console);
	return logger;
}

Log& Log::Debug()
{
	static Log logger(LogLevel::DEBUG_, console);
	return logger;
}

Log& Log::Warning()
{
	static Log logger(LogLevel::WARNING, console);
	return logger;
}

Log& Log::Error()
{
	static Log logger(LogLevel::ERROR_, console);
	return logger;
}


Log& Log::Fatal()
{
	static Log logger(LogLevel::FATAL, console);
	return logger;
}
