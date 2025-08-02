#include <gtest/gtest.h>
#include <vector>

#include <libcompiledb4ms/vcxproj.h>

using namespace compiledb4ms;

TEST(Vcxproj, get_directory_of_vcxproj)
{
	Vcxproj proj{ "libcompiledb4ms/vcxproj.test.vcxproj" };

	std::filesystem::path expected = std::filesystem::current_path()
		/ "libcompiledb4ms";
	ASSERT_EQ(proj.directory(), expected);
}

TEST(Vcxproj, extract_cl_compile_file_from_vcxproj_file)
{
	Vcxproj proj{ "libcompiledb4ms/vcxproj.test.vcxproj" };

	std::vector<std::filesystem::path> expected{
		"D:\\!dev\\WIP\\tools\\toolchain\\compiledb4ms\\tests\\usage.cpp"
	};
	ASSERT_EQ(proj.cl_compile_files(), expected);
}

TEST(Vcxproj, extract_preprocessor_definitions_from_vcxproj_file)
{
	Vcxproj proj{ "libcompiledb4ms/vcxproj.test.vcxproj" };

	std::string expected{
		R"(/D _MBCS /D WIN32 /D _WINDOWS /D GTEST_LINKED_AS_SHARED_LIBRARY=1 /D "CMAKE_INTDIR=\"Debug\"")"
	};
	ASSERT_EQ(proj.preprocessor_definitions(), expected);
}

TEST(Vcxproj, extract_additional_options_from_vcxproj_file)
{
	Vcxproj proj{ "libcompiledb4ms/vcxproj.test.vcxproj" };

	std::string expected{
		R"(/external:I "D:/!dev/WIP/tools/toolchain/compiledb4ms/build/vcpkg_installed/x64-windows/include")"
	};
	ASSERT_EQ(proj.additional_options(), expected);
}

TEST(Vcxproj, extract_std_from_vcxproj_file)
{
	Vcxproj proj{ "libcompiledb4ms/vcxproj.test.vcxproj" };

	std::string expected{
		R"(/std:c++17)"
	};
	ASSERT_EQ(proj.std(), expected);
}

TEST(Vcxproj, extract_runtime_library_from_vcxproj_file)
{
	Vcxproj proj{ "libcompiledb4ms/vcxproj.test.vcxproj" };

	std::string expected{
		R"(/MDd)"
	};
	ASSERT_EQ(proj.runtime_library(), expected);
}

TEST(Vcxproj, extract_floating_point_model_from_vcxproj_file)
{
	Vcxproj proj{ "libcompiledb4ms/vcxproj.test.vcxproj" };

	std::string expected{
		R"(/fp:precise)"
	};
	ASSERT_EQ(proj.floating_point_model(), expected);
}

TEST(Vcxproj, extract_exception_handling_from_vcxproj_file)
{
	Vcxproj proj{ "libcompiledb4ms/vcxproj.test.vcxproj" };

	std::string expected{
		R"(/EHsc)"
	};
	ASSERT_EQ(proj.exception_handling(), expected);
}

TEST(Vcxproj, extract_security_check_from_vcxproj_file)
{
	Vcxproj proj{ "libcompiledb4ms/vcxproj.test.vcxproj" };

	std::string expected{
		R"(/GS)"
	};
	ASSERT_EQ(proj.security_check(), expected);
}

TEST(Vcxproj, extract_basic_runtime_checks_from_vcxproj_file)
{
	Vcxproj proj{ "libcompiledb4ms/vcxproj.test.vcxproj" };

	std::string expected{
		R"(/RTC1)"
	};
	ASSERT_EQ(proj.basic_runtime_checks(), expected);
}

TEST(Vcxproj, extract_inline_function_expansion_from_vcxproj_file)
{
	Vcxproj proj{ "libcompiledb4ms/vcxproj.test.vcxproj" };

	std::string expected{
		R"(/Ob0)"
	};
	ASSERT_EQ(proj.inline_function_expansion(), expected);
}

TEST(Vcxproj, extract_optimization_from_vcxproj_file)
{
	Vcxproj proj{ "libcompiledb4ms/vcxproj.test.vcxproj" };

	std::string expected{
		R"(/Od)"
	};
	ASSERT_EQ(proj.optimization(), expected);
}

TEST(Vcxproj, extract_diagnostics_format_from_vcxproj_file)
{
	Vcxproj proj{ "libcompiledb4ms/vcxproj.test.vcxproj" };

	std::string expected{
		R"(/diagnostics:column)"
	};
	ASSERT_EQ(proj.diagnostics_format(), expected);
}

TEST(Vcxproj, extract_treat_warnings_as_errors_from_vcxproj_file)
{
	Vcxproj proj{ "libcompiledb4ms/vcxproj.test.vcxproj" };

	std::string expected{
		R"(/WX-)"
	};
	ASSERT_EQ(proj.treat_warnings_as_errors(), expected);
}

TEST(Vcxproj, extract_warning_level_from_vcxproj_file)
{
	Vcxproj proj{ "libcompiledb4ms/vcxproj.test.vcxproj" };

	std::string expected{
		R"(/W1)"
	};
	ASSERT_EQ(proj.warning_level(), expected);
}

TEST(Vcxproj, extract_suppress_startup_banner_from_vcxproj_file)
{
	Vcxproj proj{ "libcompiledb4ms/vcxproj.test.vcxproj" };

	std::string expected{
		R"(/nologo)"
	};
	ASSERT_EQ(proj.suppress_startup_banner(), expected);
}

TEST(Vcxproj, extract_debug_information_format_from_vcxproj_file)
{
	Vcxproj proj{ "libcompiledb4ms/vcxproj.test.vcxproj" };

	std::string expected{
		R"(/Zi)"
	};
	ASSERT_EQ(proj.debug_information_format(), expected);
}

TEST(Vcxproj, extract_internal_compiler_error_reporting_from_vcxproj_file)
{
	Vcxproj proj{ "libcompiledb4ms/vcxproj.test.vcxproj" };

	std::string expected{
		R"(/errorReport:queue)"
	};
	ASSERT_EQ(proj.internal_compiler_error_reporting(), expected);
}

TEST(Vcxproj, extract_compile_as_from_vcxproj_file)
{
	Vcxproj proj{ "libcompiledb4ms/vcxproj.test.vcxproj" };

	std::string expected{
		R"(/TP)"
	};
	ASSERT_EQ(proj.compile_as(), expected);
}

TEST(Vcxproj, extract_calling_convension_from_vcxproj_file)
{
	Vcxproj proj{ "libcompiledb4ms/vcxproj.test.vcxproj" };

	std::string expected{
		R"(/Gd)"
	};
	ASSERT_EQ(proj.calling_convension(), expected);
}

TEST(Vcxproj, extract_external_header_warning_level_from_vcxproj_file)
{
	Vcxproj proj{ "libcompiledb4ms/vcxproj.test.vcxproj" };

	std::string expected{
		R"(/external:W0)"
	};
	ASSERT_EQ(proj.external_header_warning_level(), expected);
}

TEST(Vcxproj, extract_program_database_file_name_from_vcxproj_file)
{
	Vcxproj proj{ "libcompiledb4ms/vcxproj.test.vcxproj" };

	std::string expected{
		R"(/Fd"acceptance_test.dir\Debug\vc143.pdb")"
	};
	ASSERT_EQ(proj.program_database_file_name(), expected);
}

TEST(Vcxproj, extract_object_file_name_from_vcxproj_file)
{
	Vcxproj proj{ "libcompiledb4ms/vcxproj.test.vcxproj" };

	std::string expected{
		R"(/Fo"acceptance_test.dir\Debug\\")"
	};
	ASSERT_EQ(proj.object_file_name(), expected);
}

TEST(Vcxproj, extract_additional_include_directories_from_vcxproj_file)
{
	Vcxproj proj{ "libcompiledb4ms/vcxproj.test.vcxproj" };

	std::string expected{
		R"(/I"D:\!dev\WIP\tools\toolchain\compiledb4ms")"
	};
	ASSERT_EQ(proj.additional_include_directories(), expected);
}

TEST(Vcxproj, get_property)
{
	Vcxproj proj{ "libcompiledb4ms/vcxproj.test.vcxproj" };

	std::string expected{
		R"(acceptance_test.dir\Debug\)"
	};
	ASSERT_EQ(proj.get_property("IntDir"), expected);
	ASSERT_EQ(proj.get_property("PlatformToolsetVersion"), "143");
}

TEST(Vcxproj, resolve_property)
{
	Vcxproj proj{ "libcompiledb4ms/vcxproj.test.vcxproj" };

	std::string expected{
		R"(1acceptance_test.dir\Debug\2)"
	};
	ASSERT_EQ(proj.resolve_property("1$(IntDir)2"), expected);
	ASSERT_EQ(proj.resolve_property("$(don't exists)"), "");
}

TEST(Vcxproj, init_with_arch)
{
	{
		Vcxproj proj{ "libcompiledb4ms/vcxproj.test.vcxproj", "Debug|x64" };
		ASSERT_EQ(proj.get_property("IntDir"), R"(acceptance_test.dir\Debug\)");
	}
	{
		Vcxproj proj{ "libcompiledb4ms/vcxproj.test.vcxproj", "Release|x64" };
		ASSERT_EQ(proj.get_property("IntDir"), R"(acceptance_test.dir\Release\)");
	}
}

TEST(Vcxproj, get_compile_objects)
{
	Vcxproj proj{ "libcompiledb4ms/vcxproj.test.vcxproj", "Debug|x64" };

	std::vector<Command_object> expected{
		{
			std::filesystem::current_path() / "libcompiledb4ms",
			"D:\\!dev\\WIP\\tools\\toolchain\\compiledb4ms\\tests\\usage.cpp",
			"\"D:\\Program Files\\Microsoft Visual Studio\\2022\\Enterprise\\VC\\Tools\\MSVC\\14.43.34808\\bin\\Hostx64\\x64\\cl.exe\" /c /I\"D:\\!dev\\WIP\\tools\\toolchain\\compiledb4ms\" /Zi /nologo /W1 /WX- /diagnostics:column /Od /Ob0 /D _MBCS /D WIN32 /D _WINDOWS /D GTEST_LINKED_AS_SHARED_LIBRARY=1 /D \"CMAKE_INTDIR=\\\"Debug\\\"\" /EHsc /RTC1 /MDd /GS /fp:precise /std:c++17 /Fo\"acceptance_test.dir\\Debug\\\\\" /Fd\"acceptance_test.dir\\Debug\\vc143.pdb\" /external:W0 /Gd /TP /errorReport:queue  /external:I \"D:/!dev/WIP/tools/toolchain/compiledb4ms/build/vcpkg_installed/x64-windows/include\" \"D:\\!dev\\WIP\\tools\\toolchain\\compiledb4ms\\tests\\usage.cpp\"",
		}
	};
	ASSERT_EQ(proj.command_objects(), expected);
}
