#include <gtest/gtest.h>
#include <vector>

#include <libcompiledb4ms/vcxproj.h>

using namespace compiledb4ms;

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
