#include <filesystem>
#include <string>
#include <vector>

struct Command_object {
	// The working directory of the compilation.
	// All paths specified in the command or file fields must be either absolute or relative to this directory.
	std::filesystem::path directory;

	// The main translation unit source processed by this compilation step.
	// This is used by tools as the key into the compilation database.
	// There can be multiple command objects for the same file, for example if the same source file is compiled with different configurations.
	std::filesystem::path file;

	// The compile command argv as list of strings.
	// This should run the compilation step for the translation unit file.
	// arguments[0] should be the executable name, such as clang++.
	// Arguments should not be escaped, but ready to pass to execvp().
	std::vector<std::string> arguments;

	// The compile command as a single shell-escaped string.
	// Arguments may be shell quoted and escaped following platform conventions, with ‘"’ and ‘\’ being the only special characters.
	// Shell expansion is not supported.
	// std::string command;

	// Either arguments or command is required.
	// arguments is preferred, as shell (un)escaping is a possible source of errors.

	// The name of the output created by this compilation step.
	// This field is optional.
	// It can be used to distinguish different processing modes of the same input file.
	std::filesystem::path output{};

        std::string str();
};
