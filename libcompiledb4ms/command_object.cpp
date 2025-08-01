#include <libcompiledb4ms/command_object.h>
#include <iomanip>
#include <sstream>
#include <variant>

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

template<class... Ts>
struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

}

namespace compiledb4ms {

std::string Command_object::str() const
{
	std::ostringstream os;
	os << '{' << newline;
	os << R"(  "directory": )" << directory << ',' << newline;
	os << R"(  "file": )" << file << ',' << newline;

	std::visit(overloaded{
		[&](const std::vector<std::string>& arguments) {
			os << R"(  "arguments": )" << '[' << newline;
			output_arguments(os, arguments);
			os << R"(  ])" << newline;
		},
		[&](const std::string& command) {
			os << R"(  "command": )" << std::quoted(command) << newline;
		},
	}, arguments);

	os << '}';
	return os.str();
}

bool operator==(const Command_object& lhs, const Command_object& rhs)
{
	return lhs.directory == rhs.directory
		&& lhs.file == rhs.file
		&& lhs.arguments == rhs.arguments
		&& lhs.output == rhs.output
		;
}

std::ostream& operator<<(std::ostream& os, const Command_object& obj)
{
	return os << obj.str();
}

}
