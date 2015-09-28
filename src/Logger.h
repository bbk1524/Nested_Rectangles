#pragma once

#include <ostream>
#include <memory>
#include <fstream>
#include <iostream>
#include <string>

#define STR(x) #x
#define STRINGIFY(x) STR(x)

#if  defined(_MSC_VER)
# define FUNCTION_NAME __FUNCSIG__
#elif defined(__clang__)
# define FUNCTION_NAME  STR(function_name_not_available)
#elif defined(__GNUCC__) || defined(__GNUG__)
# define FUNCTION_NAME __PRETTY_FUNCTION__
#endif

#define SEP " -- "
#define FILE_INFO SEP __FILE__ SEP FUNCTION_NAME SEP STRINGIFY(__LINE__) SEP

#define COND(x) x, STRINGIFY(x) 

class Logger {
private:
	std::shared_ptr<std::ostream> output_stream{ nullptr };

public:
	Logger();

	Logger(std::string file);

	// default destructor is OK
	~Logger() = default;

	template<typename First>
	void log(First info)
	{
		*output_stream << info << std::endl;
	}

	template<typename First, typename... Rest>
	void log(First first, Rest... rest)
	{
		*output_stream << first << ' ';
		log(rest...);
	}

	//must be called with a condiiton and at least one arg
	template<typename... Rest>
	void check(bool cond, Rest... rest)
	{
		if (!cond)
		{
			log(rest...);
		}
	}
};
