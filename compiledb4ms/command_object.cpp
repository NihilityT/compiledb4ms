#include <compiledb4ms/command_object.h>
#include <iomanip>
#include <sstream>

namespace
{

constexpr char newline = '\n';

void output_arguments(std::ostringstream& os,
	const std::vector<std::string>& arguments)
{
	size_t size = arguments.size();
	for (size_t i = 0; i < size; ++i)
	{
		if (i)
		{
			os << ',' << newline;
		}
		os << "    " << std::quoted(arguments[i]);
	}
	os << newline;
}

}

std::string Command_object::str()
{
	std::ostringstream os;
	os << '{' << newline;
	os << R"(  "directory": )" << directory << ',' << newline;
	os << R"(  "file": )" << file << ',' << newline;
	os << R"(  "arguments": )" << '[' << newline;
	output_arguments(os, arguments);
	os << R"(  ])" << newline;
	os << '}';
	return os.str();
}
