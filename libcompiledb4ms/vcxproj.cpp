#include <libcompiledb4ms/vcxproj.h>
#include <libcompiledb4ms/utils.h>
#include <libutils/utils.h>

#include <algorithm>
#include <regex>
#include <sstream>
#include <vector>

namespace {

std::string warning_level(std::string_view warning)
{
	if (warning == "TurnOffAllWarnings") {
		return "W0";
	} else if (warning == "Level1") {
		return "W1";
	} else if (warning == "Level2") {
		return "W2";
	} else if (warning == "Level3") {
		return "W3";
	} else if (warning == "Level4") {
		return "W4";
	} else if (warning == "EnableAllWarnings") {
		return "Wall";
	}
	return "W1";
}

std::string get_arch_condition(std::string_view arch = "Debug|x64")
{
	std::ostringstream os;
	os << "'$(Configuration)|$(Platform)'=='" << arch << "'";
	return os.str();
}

bool is_match_arch_condition(const pugi::xml_node& node, std::string_view arch_condition)
{
	pugi::xml_attribute condition = node.attribute("Condition");
	return condition.empty() || condition.value() == arch_condition;
}

}

namespace compiledb4ms {

Vcxproj::Vcxproj(const std::filesystem::path& path, std::string_view arch /*= "Debug|x64"*/)
	: m_proj_path(path)
	, m_arch_condition(get_arch_condition(arch))
{
	m_doc.load_file(path.c_str());
	m_project = m_doc.child("Project");
}

std::vector<Command_object> Vcxproj::command_objects() const
{
	std::vector<Command_object> res;
	for (auto& cl_compile_file : cl_compile_files()) {
		res.emplace_back(Command_object{
			 directory(),
			 cl_compile_file,
			 '"' + utils::get_cl_path().string() + "\" /c "
			 + debug_information_format() + " "
			 + suppress_startup_banner() + " "
			 + warning_level() + " "
			 + treat_warnings_as_errors() + " "
			 + diagnostics_format() + " "
			 + optimization() + " "
			 + inline_function_expansion() + " "
			 + preprocessor_definitions() + " "
			 + exception_handling() + " "
			 + basic_runtime_checks() + " "
			 + runtime_library() + " "
			 + security_check() + " "
			 + floating_point_model() + " "
			 + std() + " "
			 + object_file_name() + " "
			 + program_database_file_name() + " "
			 + external_header_warning_level() + " "
			 + calling_convension() + " "
			 + compile_as() + " "
			 + internal_compiler_error_reporting() + " "
			 " " + additional_options() + " "
			 "\"" + cl_compile_file.string() + '"',
		});
	}
	return res;
}

std::filesystem::path Vcxproj::directory() const
{
	return std::filesystem::absolute(m_proj_path).parent_path();
}

std::string Vcxproj::preprocessor_definitions() const
{
	auto item_definition_group = get_arch("ItemDefinitionGroup");
	auto preprocessor_definitions = ::utils::split(
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

std::string Vcxproj::additional_options() const
{
	auto item_definition_group = get_arch("ItemDefinitionGroup");
	std::string additional_options = item_definition_group.child("ClCompile")
		.child("AdditionalOptions").first_child().value();
	::utils::replace(additional_options, "%(AdditionalOptions) ", "");
	return additional_options;
}

std::vector<std::filesystem::path> Vcxproj::cl_compile_files() const
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

std::string Vcxproj::std() const
{
	auto item_definition_group = get_arch("ItemDefinitionGroup");
	std::string language_standard = item_definition_group.child("ClCompile")
		.child("LanguageStandard").first_child().value();
	::utils::replace(language_standard, "stdcpp", "/std:c++");
	return language_standard;
}

std::string Vcxproj::runtime_library() const
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

std::string Vcxproj::floating_point_model() const
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

std::string Vcxproj::exception_handling() const
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

std::string Vcxproj::security_check() const
{
	auto item_definition_group = get_arch("ItemDefinitionGroup");
	std::string bsc = item_definition_group.child("ClCompile")
		.child("BufferSecurityCheck").first_child().value();
	if (bsc == "false") {
		return "/GS-";
	}
	return "/GS";
}

std::string Vcxproj::basic_runtime_checks() const
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

std::string Vcxproj::inline_function_expansion() const
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

std::string Vcxproj::optimization() const
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

std::string Vcxproj::diagnostics_format() const
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

std::string Vcxproj::treat_warnings_as_errors() const
{
	auto item_definition_group = get_arch("ItemDefinitionGroup");
	std::string wae = item_definition_group.child("ClCompile")
		.child("TreatWarningAsError").first_child().value();
	if (wae == "true") {
		return "/WX";
	}
	return "/WX-";
}

std::string Vcxproj::warning_level() const
{
	auto item_definition_group = get_arch("ItemDefinitionGroup");
	std::string wl = item_definition_group.child("ClCompile")
		.child("WarningLevel").first_child().value();

	return "/" + ::warning_level(wl);
}

std::string Vcxproj::suppress_startup_banner() const
{
	auto item_definition_group = get_arch("ItemDefinitionGroup");
	std::string ssb = item_definition_group.child("ClCompile")
		.child("SuppressStartupBanner").first_child().value();

	if (ssb == "false") {
		return "";
	}
	return "/nologo";
}

std::string Vcxproj::debug_information_format() const
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

std::string Vcxproj::internal_compiler_error_reporting() const
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

std::string Vcxproj::compile_as() const
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

std::string Vcxproj::calling_convension() const
{
	auto item_definition_group = get_arch("ItemDefinitionGroup");
	std::string cc = item_definition_group.child("ClCompile")
		.child("CallingConvention").first_child().value();

	if (cc == "Cdecl") {
		return "/Gd";
	} else if (cc == "FastCall") {
		return "/Gr";
	} else if (cc == "StdCall") {
		return "/Gz";
	} else if (cc == "VectorCall") {
		return "/Gv";
	}
	return "/Gd";
}

std::string Vcxproj::external_header_warning_level() const
{
	auto item_definition_group = get_arch("ItemDefinitionGroup");
	std::string ewl = item_definition_group.child("ClCompile")
		.child("ExternalWarningLevel").first_child().value();

	if (ewl == "InheritWarningLevel") {
		std::string res = warning_level();
		if (res == "/Wall") {
			return "/external:W4";
		}
		return "/external:" + res.substr(1);
	}
	return "/external:" + ::warning_level(ewl);
}

std::string Vcxproj::program_database_file_name() const
{
	auto item_definition_group = get_arch("ItemDefinitionGroup");
	std::string pdbfn = item_definition_group.child("ClCompile")
		.child("ProgramDataBaseFileName").first_child().value();

	return "/Fd\"" + (pdbfn.empty()
		? resolve_property("$(IntDir)vc$(PlatformToolsetVersion).pdb")
		: resolve_property(pdbfn)) + '"';
}

std::string Vcxproj::object_file_name() const
{
	auto item_definition_group = get_arch("ItemDefinitionGroup");
	std::string ofn = item_definition_group.child("ClCompile")
		.child("ObjectFileName").first_child().value();

	return "/Fo\"" + resolve_property(ofn) + R"(\")";
}

std::string Vcxproj::get_property(const std::string& property) const
{
	if (property == "PlatformToolsetVersion") {
		return get_property("PlatformToolset").substr(1);
	}

	for (pugi::xml_node group : m_project.children("PropertyGroup")) {
		if (!is_match_arch_condition(group, m_arch_condition)) {
			continue;
		}

		for (pugi::xml_node property_node : group.children(property.c_str())) {
			if (is_match_arch_condition(property_node, m_arch_condition)) {
				return property_node.first_child().value();
			}
		}
	}
	return {};
}

std::string Vcxproj::resolve_property(const std::string& expression) const
{
	std::regex variable{ R"(\$\(([^)]+)\))" };
	auto begin = expression.cbegin();
	auto end = expression.cend();

	std::string res;
	std::smatch sm;
	while (std::regex_search(begin, end, sm, variable)) {
		std::string var = sm[1];
		res.append(begin, sm[0].first);
		res.append(get_property(sm[1].str()));
		begin = sm[0].second;
	}
	res.append(begin, end);
	return res;
}

pugi::xml_node Vcxproj::get_arch(const char* name) const
{
	return m_project.find_child_by_attribute(name,
		"Condition", m_arch_condition.c_str());
}

}
