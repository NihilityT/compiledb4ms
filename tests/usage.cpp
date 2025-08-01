#include <gtest/gtest.h>

#include <stdlib.h>

#include <string>

#include <libutils/utils.h>

TEST(Usage, generate_compiledb_for_vcxproj)
{
	std::string compiledb4ms = utils::get_env("compiledb4ms", "compiledb4ms");
	std::string cmd = compiledb4ms + " -p tests/usage.vcxproj";
	int exit_code = system(cmd.c_str());
	ASSERT_EQ(0, exit_code);

	auto res = utils::read_file("compile_commands.json");
	std::string expected = R"([
{
  "directory": "D:\\!dev\\WIP\\tools\\toolchain\\compiledb4ms\\tests",
  "file": "D:\\!dev\\WIP\\tools\\toolchain\\compiledb4ms\\tests\\usage.cpp",
  "command": "\"D:\\Program Files\\Microsoft Visual Studio\\2022\\Enterprise\\VC\\Tools\\MSVC\\14.43.34808\\bin\\Hostx64\\x64\\cl.exe\" /c /Zi /nologo /W4 /WX /diagnostics:column /Od /Ob0 /D _MBCS /D WIN32 /D _WINDOWS /D GTEST_LINKED_AS_SHARED_LIBRARY=1 /D \"CMAKE_INTDIR=\\\"Debug\\\"\" /EHsc /RTC1 /MDd /GS /fp:precise /std:c++17 /Fo\"acceptance_test.dir\\Debug\\\\\" /Fd\"acceptance_test.dir\\Debug\\vc143.pdb\" /external:W0 /Gd /TP /errorReport:queue  /external:I \"D:/!dev/WIP/tools/toolchain/compiledb4ms/build/vcpkg_installed/x64-windows/include\" \"D:\\!dev\\WIP\\tools\\toolchain\\compiledb4ms\\tests\\usage.cpp\""
}
])";
	ASSERT_EQ(res, expected);
// original
// D:\Program Files\Microsoft Visual Studio\2022\Enterprise\VC\Tools\MSVC\14.43.34808\bin\HostX64\x64\CL.exe /c /Zi /nologo /W4 /WX /diagnostics:column /Od /Ob0 /D _MBCS /D WIN32 /D _WINDOWS /D GTEST_LINKED_AS_SHARED_LIBRARY=1 /D "CMAKE_INTDIR=\"Debug\"" /EHsc /RTC1 /MDd /GS /fp:precise /std:c++17 /Fo"acceptance_test.dir\Debug\\" /Fd"acceptance_test.dir\Debug\vc143.pdb" /external:W0 /Gd /TP /errorReport:queue  /external:I "D:/!dev/WIP/tools/toolchain/compiledb4ms/build/vcpkg_installed/x64-windows/include" "D:\!dev\WIP\tools\toolchain\compiledb4ms\tests\usage.cpp"
}
