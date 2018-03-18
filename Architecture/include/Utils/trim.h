#pragma once

#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

namespace Utils
{
	static inline void trim_front(std::string &s) {
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
			return !std::isspace(ch);
		}));
	}

	static inline void trim_back(std::string &s) {
		s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
			return !std::isspace(ch);
		}).base(), s.end());
	}


	static inline void trim(std::string &s) {
		trim_front(s);
		trim_back(s);
	}


	static inline std::string trim_front_copy(std::string s) {
		trim_front(s);
		return s;
	}

	static inline std::string trim_back_copy(std::string s) {
		trim_back(s);
		return s;
	}

	static inline std::string trim_copy(std::string s) {
		trim(s);
		return s;
	}
}
