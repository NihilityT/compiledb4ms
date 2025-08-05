#include <gtest/gtest.h>

#include <stdlib.h>

#include <string>

#include <libutils/utils.h>
#include <libcompiledb4ms/command_object.h>
#include <libcompiledb4ms/utils.h>

TEST(Usage, generate_compiledb_for_vcxproj)
{
	std::string compiledb4ms = utils::get_env("compiledb4ms", "compiledb4ms");
	std::string cmd = compiledb4ms + " -p tests/usage.vcxproj";
	int exit_code = system(cmd.c_str());
	ASSERT_EQ(0, exit_code);

	auto res = utils::read_file("compile_commands.json");
	compiledb4ms::Command_object expected{
		std::filesystem::current_path() / "tests",
		R"(D:\!dev\WIP\tools\toolchain\compiledb4ms\tests\usage.cpp)",
		'"' + compiledb4ms::utils::get_cl_path().string() + R"(" /c /I"D:\!dev\WIP\tools\toolchain\compiledb4ms" /Zi /nologo /W4 /WX /diagnostics:column /Od /Ob0 /D _MBCS /D WIN32 /D _WINDOWS /D GTEST_LINKED_AS_SHARED_LIBRARY=1 /D "CMAKE_INTDIR=\"Debug\"" /EHsc /RTC1 /MDd /GS /fp:precise /std:c++17 /Fo"acceptance_test.dir\Debug\\" /Fd"acceptance_test.dir\Debug\vc143.pdb" /external:W0 /Gd /TP /errorReport:queue  /external:I "D:/!dev/WIP/tools/toolchain/compiledb4ms/build/vcpkg_installed/x64-windows/include" "D:\!dev\WIP\tools\toolchain\compiledb4ms\tests\usage.cpp")",
	};
	ASSERT_EQ(res, "[\n" + expected.str() + "\n]");
}

TEST(Usage, generate_compiledb_for_vcxproj_with_release_x64_type)
{
	std::string compiledb4ms = utils::get_env("compiledb4ms", "compiledb4ms");
	std::string cmd = std::string(compiledb4ms) + R"( -t "Release|x64" -p tests/usage.vcxproj)";
	int exit_code = system(cmd.c_str());
	ASSERT_EQ(0, exit_code);

	auto res = utils::read_file("compile_commands.json");
	compiledb4ms::Command_object expected{
		std::filesystem::current_path() / "tests",
		R"(D:\!dev\WIP\tools\toolchain\compiledb4ms\tests\usage.cpp)",
		'"' + compiledb4ms::utils::get_cl_path().string() + R"(" /c /I"D:\!dev\WIP\tools\toolchain\compiledb4ms"  /nologo /W4 /WX /diagnostics:column /O2 /Ob2 /D _MBCS /D WIN32 /D _WINDOWS /D NDEBUG /D GTEST_LINKED_AS_SHARED_LIBRARY=1 /D "CMAKE_INTDIR=\"Release\"" /EHsc  /MD /GS /fp:precise /std:c++17 /Fo"acceptance_test.dir\Release\\" /Fd"acceptance_test.dir\Release\vc143.pdb" /external:W0 /Gd /TP /errorReport:queue  /external:I "D:/!dev/WIP/tools/toolchain/compiledb4ms/build/vcpkg_installed/x64-windows/include" "D:\!dev\WIP\tools\toolchain\compiledb4ms\tests\usage.cpp")",
	};
	ASSERT_EQ(res, "[\n" + expected.str() + "\n]");
}

TEST(Usage, generate_compiledb_for_sln)
{
	std::string compiledb4ms = utils::get_env("compiledb4ms", "compiledb4ms");
	std::string cmd = std::string(compiledb4ms) + R"( -s tests/usage.sln)";
	int exit_code = system(cmd.c_str());
	ASSERT_EQ(0, exit_code);

	auto res = utils::read_file("compile_commands.json");
	compiledb4ms::Command_object expected{
		std::filesystem::current_path() / "tests",
		R"(D:\!dev\WIP\tools\toolchain\compiledb4ms\tests\usage.cpp)",
		'"' + compiledb4ms::utils::get_cl_path().string() + R"(" /c /I"D:\!dev\WIP\tools\toolchain\compiledb4ms" /Zi /nologo /W4 /WX /diagnostics:column /Od /Ob0 /D _MBCS /D WIN32 /D _WINDOWS /D GTEST_LINKED_AS_SHARED_LIBRARY=1 /D "CMAKE_INTDIR=\"Debug\"" /EHsc /RTC1 /MDd /GS /fp:precise /std:c++17 /Fo"acceptance_test.dir\Debug\\" /Fd"acceptance_test.dir\Debug\vc143.pdb" /external:W0 /Gd /TP /errorReport:queue  /external:I "D:/!dev/WIP/tools/toolchain/compiledb4ms/build/vcpkg_installed/x64-windows/include" "D:\!dev\WIP\tools\toolchain\compiledb4ms\tests\usage.cpp")",
	};
	ASSERT_EQ(res, "[\n" + expected.str() + "\n]");
}
