#pragma once
#include <exception>
#include <string>

namespace Core
{
	namespace Debug
	{
		class Assertion : public std::exception
		{
		private:
			const char* m_expression;
			const char* m_file;
			int m_line;
			std::string m_message;
			std::string m_report;

		public:
			Assertion(const char* p_expression, const char* p_file, int p_line, const std::string& p_message);
			~Assertion() throw();

			void LogError() const;

			virtual const char* what() const throw();
			const char* Expression() const throw();
			const char* File() const throw();
			int Line() const throw();
			const char* Message() const throw();
		};

		#define ASSERT(EXPRESSION, MESSAGE) if(!(EXPRESSION)) { throw Core::Debug::Assertion(#EXPRESSION, __FILE__, __LINE__, MESSAGE); }
	}
}
