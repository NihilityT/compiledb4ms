#include <libcompiledb4ms/vcxproj.h>
#include <libutils/utils.h>

#include <algorithm>
#include <sstream>

namespace compiledb4ms {

Vcxproj::Vcxproj(const std::filesystem::path& path)
{
	m_doc.load_file(path.c_str());
	m_project = m_doc.child("Project");
}

std::string Vcxproj::preprocessor_definitions()
{
	auto item_definition_group = get_arch("ItemDefinitionGroup");
	auto preprocessor_definitions = utils::split(
		item_definition_group.child("ClCompile")
		.child("PreprocessorDefinitions")
		.first_child().value());

	auto inherit_definitions = std::find(preprocessor_definitions.begin(), preprocessor_definitions.end(), "%(PreprocessorDefinitions)");
	if (inherit_definitions != preprocessor_definitions.cend())
	{
		std::string character_set = get_arch("PropertyGroup")
			.child("CharacterSet").first_child().value();
		if (character_set == "MultiByte") {
			*inherit_definitions = "_MBCS";
		} else if (character_set == "Unicode") {
			*inherit_definitions = "_UNICODE";
		} else {
			preprocessor_definitions.erase(inherit_definitions);
		}
	}

	std::ostringstream definitions;
	for (auto& definition : preprocessor_definitions)
	{
		if (definitions.tellp())
		{
			definitions << " ";
		}
		definitions << "/D ";
		if (definition.find("=\"") == definition.npos)
		{
			definitions << definition;
		}
		else
		{
			definitions << std::quoted(definition);
		}
	}

	return definitions.str();
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

pugi::xml_node Vcxproj::get_arch(const char* name, const char* arch /*= "Debug|x64"*/)
{
	auto arch_condition = std::string{ "'$(Configuration)|$(Platform)'=='" } + arch + "'";
	return m_project.find_child_by_attribute(name,
		"Condition", arch_condition.c_str());
}

}
