#include <libcompiledb4ms/vcxproj.h>
#include <libutils/utils.h>

#include <algorithm>
#include <sstream>

namespace compiledb4ms {

Vcxproj::Vcxproj(const std::filesystem::path& path)
	: m_proj_path(path)
{
	m_doc.load_file(path.c_str());
	m_project = m_doc.child("Project");
}

std::filesystem::path Vcxproj::directory()
{
	return std::filesystem::absolute(m_proj_path).parent_path();
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

std::string Vcxproj::additional_options()
{
	auto item_definition_group = get_arch("ItemDefinitionGroup");
	std::string additional_options = item_definition_group.child("ClCompile")
		.child("AdditionalOptions").first_child().value();
	utils::replace(additional_options, "%(AdditionalOptions) ", "");
	return additional_options;
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

std::string Vcxproj::std()
{
	auto item_definition_group = get_arch("ItemDefinitionGroup");
	std::string language_standard = item_definition_group.child("ClCompile")
		.child("LanguageStandard").first_child().value();
	utils::replace(language_standard, "stdcpp", "/std:c++");
	return language_standard;
}

std::string Vcxproj::runtime_library()
{
	auto item_definition_group = get_arch("ItemDefinitionGroup");
	std::string library = item_definition_group.child("ClCompile")
		.child("RuntimeLibrary").first_child().value();
	if (library == "MultiThreaded") {
		return "/MT";
	} else if (library == "MultiThreadedDebug") {
		return "/MTd";
	} else if (library == "MultiThreadedDLL") {
		return "/MD";
	} else if (library == "MultiThreadedDebugDLL") {
		return "/MDd";
	}
	return "";
}

std::string Vcxproj::floating_point_model()
{
	auto item_definition_group = get_arch("ItemDefinitionGroup");
	std::string model = item_definition_group.child("ClCompile")
		.child("FloatingPointModel").first_child().value();
	if (model == "Precise") {
		return "/fp:precise";
	} else if (model == "Strict") {
		return "/fp:strict";
	} else if (model == "Fast") {
		return "/fp:fast";
	}
	return "/fp:precise";
}

std::string Vcxproj::exception_handling()
{
	auto item_definition_group = get_arch("ItemDefinitionGroup");
	std::string eh = item_definition_group.child("ClCompile")
		.child("ExceptionHandling").first_child().value();
	if (eh == "Sync") {
		return "/EHsc";
	} else if (eh == "Async") {
		return "/EHa";
	} else if (eh == "SyncCThrow") {
		return "/EHs";
	}
	return "";
}

std::string Vcxproj::security_check()
{
	auto item_definition_group = get_arch("ItemDefinitionGroup");
	std::string bsc = item_definition_group.child("ClCompile")
		.child("BufferSecurityCheck").first_child().value();
	if (bsc == "false") {
		return "/GS-";
	}
	return "/GS";
}

std::string Vcxproj::basic_runtime_checks()
{
	auto item_definition_group = get_arch("ItemDefinitionGroup");
	std::string brc = item_definition_group.child("ClCompile")
		.child("BasicRuntimeChecks").first_child().value();
	if (brc == "StackFrameRuntimeCheck") {
		return "/RTCs";
	} else if (brc == "UninitializedLocalUsageCheck") {
		return "/RTCu";
	} else if (brc == "EnableFastChecks") {
		return "/RTC1";
	}
	return "";
}

std::string Vcxproj::inline_function_expansion()
{
	auto item_definition_group = get_arch("ItemDefinitionGroup");
	std::string ife = item_definition_group.child("ClCompile")
		.child("InlineFunctionExpansion").first_child().value();
	if (ife == "Disabled") {
		return "/Ob0";
	} else if (ife == "OnlyExplicitInline") {
		return "/Ob1";
	} else if (ife == "AnySuitable") {
		return "/Ob2";
	}
	return "";
}

std::string Vcxproj::optimization()
{
	auto item_definition_group = get_arch("ItemDefinitionGroup");
	std::string optimization = item_definition_group.child("ClCompile")
		.child("Optimization").first_child().value();
	if (optimization == "Disabled") {
		return "/Od";
	} else if (optimization == "MinSpace") {
		return "/O1";
	} else if (optimization == "MaxSpeed") {
		return "/O2";
	} else if (optimization == "Full") {
		return "/Ox";
	}
	return "";
}

std::string Vcxproj::diagnostics_format()
{
	auto item_definition_group = get_arch("ItemDefinitionGroup");
	std::string df = item_definition_group.child("ClCompile")
		.child("DiagnosticsFormat").first_child().value();
	if (df == "Caret") {
		return "/diagnostics:caret";
	} else if (df == "Column") {
		return "/diagnostics:column";
	} else if (df == "Classic") {
		return "/diagnostics:classic";
	}
	return "/diagnostics:column";
}

std::string Vcxproj::treat_warnings_as_errors()
{
	auto item_definition_group = get_arch("ItemDefinitionGroup");
	std::string wae = item_definition_group.child("ClCompile")
		.child("TreatWarningAsError").first_child().value();
	if (wae == "true") {
		return "/WX";
	}
	return "/WX-";
}

std::string Vcxproj::warning_level()
{
	auto item_definition_group = get_arch("ItemDefinitionGroup");
	std::string wl = item_definition_group.child("ClCompile")
		.child("WarningLevel").first_child().value();

	if (wl == "TurnOffAllWarnings") {
		return "/W0";
	} else if (wl == "Level1") {
		return "/W1";
	} else if (wl == "Level2") {
		return "/W2";
	} else if (wl == "Level3") {
		return "/W3";
	} else if (wl == "Level4") {
		return "/W4";
	} else if (wl == "EnableAllWarnings") {
		return "/Wall";
	}
	return "/W1";
}

std::string Vcxproj::suppress_startup_banner()
{
	auto item_definition_group = get_arch("ItemDefinitionGroup");
	std::string ssb = item_definition_group.child("ClCompile")
		.child("SuppressStartupBanner").first_child().value();

	if (ssb == "false") {
		return "";
	}
	return "/nologo";
}

std::string Vcxproj::debug_information_format()
{
	auto item_definition_group = get_arch("ItemDefinitionGroup");
	std::string dif = item_definition_group.child("ClCompile")
		.child("DebugInformationFormat").first_child().value();

	if (dif == "None") {
		return "";
	} else if (dif == "OldStyle") {
		return "/Z7";
	} else if (dif == "ProgramDatabase") {
		return "/Zi";
	} else if (dif == "EditAndContinue") {
		return "/ZI";
	}
	return "";
}

std::string Vcxproj::internal_compiler_error_reporting()
{
	auto item_definition_group = get_arch("ItemDefinitionGroup");
	std::string er = item_definition_group.child("ClCompile")
		.child("ErrorReporting").first_child().value();

	if (er == "None") {
		return "/errorReport:none";
	} else if (er == "Prompt") {
		return "/errorReport:prompt";
	} else if (er == "Queue") {
		return "/errorReport:queue";
	} else if (er == "Send") {
		return "/errorReport:send";
	}
	// Specifies how internal tool errors should be reported back to Microsoft.
	// The default in the IDE is prompt.
	// The default from command line builds is queue.
	// (/errorReport:[method])
	return "/errorReport:queue";
}

std::string Vcxproj::compile_as()
{
	auto item_definition_group = get_arch("ItemDefinitionGroup");
	std::string ca = item_definition_group.child("ClCompile")
		.child("CompileAs").first_child().value();

	if (ca == "Default") {
		return "/TP"; // /TC for c, /TP for cpp
	} else if (ca == "CompileAsC") {
		return "/TC";
	} else if (ca == "CompileAsCpp") {
		return "/TP";
	} else if (ca == "CompileAsCppModule") {
		return "/interface";
	} else if (ca == "CompileAsCppModuleInternalPartition") {
		return "/internalPartition";
	} else if (ca == "CompileAsHeaderUnit") {
		return "/exportHeader";
	}
	return "/TP";
}

pugi::xml_node Vcxproj::get_arch(const char* name, const char* arch /*= "Debug|x64"*/)
{
	auto arch_condition = std::string{ "'$(Configuration)|$(Platform)'=='" } + arch + "'";
	return m_project.find_child_by_attribute(name,
		"Condition", arch_condition.c_str());
}

}
