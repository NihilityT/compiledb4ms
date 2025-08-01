#ifndef __libcompiledb4ms_vcxproj_h__
#define __libcompiledb4ms_vcxproj_h__

#include <pugixml.hpp>

#include <filesystem>
#include <string>
#include <vector>

#include <libcompiledb4ms/command_object.h>

namespace compiledb4ms {

class Vcxproj
{

public:
	Vcxproj(const std::filesystem::path& path, std::string_view arch = "Debug|x64");

	std::vector<Command_object> command_objects() const;

	std::filesystem::path directory() const;

	std::string preprocessor_definitions() const;

	std::string additional_options() const;

	std::vector<std::filesystem::path> cl_compile_files() const;

	std::string std() const;

	std::string runtime_library() const;

	std::string floating_point_model() const;

	std::string exception_handling() const;

	std::string security_check() const;

	std::string basic_runtime_checks() const;

	std::string inline_function_expansion() const;

	std::string optimization() const;

	std::string diagnostics_format() const;

	std::string treat_warnings_as_errors() const;

	std::string warning_level() const;

	std::string suppress_startup_banner() const;

	std::string debug_information_format() const;

	std::string internal_compiler_error_reporting() const;

	std::string compile_as() const;

	std::string calling_convension() const;

	std::string external_header_warning_level() const;

	std::string program_database_file_name() const;

	std::string object_file_name() const;

	std::string get_property(const std::string& property) const;
	std::string resolve_property(const std::string& expression) const;

private:
	pugi::xml_node get_arch(const char* name) const;

private:
	std::filesystem::path m_proj_path;
	pugi::xml_document m_doc;
	pugi::xml_node m_project;
	std::string m_arch_condition;
};

}

#endif // __libcompiledb4ms_vcxproj_h__
