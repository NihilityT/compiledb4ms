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
