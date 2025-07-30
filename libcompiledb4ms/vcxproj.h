#ifndef __libcompiledb4ms_vcxproj_h__
#define __libcompiledb4ms_vcxproj_h__

#include <pugixml.hpp>

#include <filesystem>
#include <vector>

namespace compiledb4ms {

class Vcxproj
{

public:
	Vcxproj(const std::filesystem::path& path);

	std::vector<std::filesystem::path> cl_compile_files();

private:
	pugi::xml_document m_doc;
	pugi::xml_node m_project;
};

}

#endif // __libcompiledb4ms_vcxproj_h__
