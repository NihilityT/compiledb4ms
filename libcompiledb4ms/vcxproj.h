#ifndef __libcompiledb4ms_vcxproj_h__
#define __libcompiledb4ms_vcxproj_h__

#include <pugixml.hpp>

#include <filesystem>
#include <string>
#include <vector>

namespace compiledb4ms {

class Vcxproj
{

public:
	Vcxproj(const std::filesystem::path& path);

	std::filesystem::path directory();

	std::string preprocessor_definitions();

	std::string additional_options();

	std::vector<std::filesystem::path> cl_compile_files();

	std::string std();

	std::string runtime_library();

	std::string floating_point_model();

	std::string exception_handling();

	std::string security_check();

	std::string basic_runtime_checks();

	std::string inline_function_expansion();

	std::string optimization();

	std::string diagnostics_format();

	std::string treat_warnings_as_errors();

	std::string warning_level();

private:
	pugi::xml_node get_arch(const char* name, const char* arch = "Debug|x64");

private:
	std::filesystem::path m_proj_path;
	pugi::xml_document m_doc;
	pugi::xml_node m_project;
};

}

#endif // __libcompiledb4ms_vcxproj_h__
