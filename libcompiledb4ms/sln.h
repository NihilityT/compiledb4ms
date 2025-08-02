#ifndef __libcompiledb4ms_sln_h__
#define __libcompiledb4ms_sln_h__

#include <libcompiledb4ms/command_object.h>

#include <filesystem>
#include <unordered_map>

namespace compiledb4ms {

class Sln {
public:
	Sln(const std::filesystem::path& path, std::string_view arch = "Debug|x64");

	std::unordered_map<std::string, std::filesystem::path> projects() const;

	std::vector<Command_object> command_objects() const;

private:
	std::filesystem::path m_sln_path;
	std::string m_arch;
};

}

#endif // __libcompiledb4ms_sln_h__
