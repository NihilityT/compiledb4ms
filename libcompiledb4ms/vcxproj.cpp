#include <libcompiledb4ms/vcxproj.h>
#include <libutils/utils.h>

namespace compiledb4ms {

Vcxproj::Vcxproj(const std::filesystem::path& path)
{
	m_doc.load_file(path.c_str());
	m_project = m_doc.child("Project");
}

std::vector<std::filesystem::path> Vcxproj::cl_compile_files()
{
	std::vector<std::filesystem::path> cl_compile_node;
	for (pugi::xml_node item_group : m_project.children("ItemGroup"))
	{
		for (pugi::xml_node cl_compile : item_group.children("ClCompile"))
		{
			cl_compile_node.push_back(cl_compile.attribute("Include").value());
		}
	}
	return cl_compile_node;
}


}
