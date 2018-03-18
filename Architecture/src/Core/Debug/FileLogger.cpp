#include <fstream>
#include "Core/Debug/FileLogger.h"
#include "Utils/Timer.h"

using namespace Core::Debug;

FileLogger::FileLogger(const char* p_filePath)
{
	std::string filepath = p_filePath;
//	size_t dotPos = filepath.find_last_of(".");
//	if (filepath.substr(dotPos) == ".txt")
//	{
//		char dayTime[50];
//		Utils::Timer::GetDayTime(dayTime);
//		filepath.insert(dotPos, dayTime);
//	}
	std::fstream m_logFile;
	m_logFile.open(filepath, std::fstream::out);
}

FileLogger::FileLogger(FileLogger&& p_fileLogger) noexcept : m_logfile(std::move(p_fileLogger.m_logfile))
{
}


FileLogger::~FileLogger()
{
	m_logfile.close();
}

void FileLogger::LogLine(const std::string& p_message, const char* p_function, const char* p_file, const int p_line,
                         const LogLevel p_level)
{
	m_logfile << ":: " << logLevelToStr(p_level) << "::  " << p_function << "() in " << p_file << "(" << p_line << ")\n" << p_message << '\n';
}
