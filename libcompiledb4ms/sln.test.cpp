#include <filesystem>
#include <gtest/gtest.h>

#include <libcompiledb4ms/sln.h>
#include <string>
#include <unordered_map>

using namespace compiledb4ms;

TEST(libcompiledb4ms_Sln, get_project_filepaths)
{
	std::filesystem::path base = std::filesystem::absolute("libcompiledb4ms");
	Sln sln{ base / "sln.test.sln" };

	std::unordered_map<std::string, std::filesystem::path> expected{
		{ "test", base / "vcxproj.test.vcxproj" },
		{ "test2", base / "vcxproj.2.test.vcxproj" },
	};
	ASSERT_EQ(sln.projects(), expected);
}

TEST(libcompiledb4ms_Sln, get_command_objects)
{
	std::filesystem::path base = std::filesystem::absolute("libcompiledb4ms");
	Sln sln{ base / "sln.test.sln" };

	std::vector<Command_object> expected{
		{
			std::filesystem::current_path() / "libcompiledb4ms",
			"D:\\!dev\\WIP\\tools\\toolchain\\compiledb4ms\\tests\\usage.cpp",
			"\"D:\\Program Files\\Microsoft Visual Studio\\2022\\Enterprise\\VC\\Tools\\MSVC\\14.43.34808\\bin\\Hostx64\\x64\\cl.exe\" /c /I\"D:\\!dev\\WIP\\tools\\toolchain\\compiledb4ms\" /Zi /nologo /W1 /WX- /diagnostics:column /Od /Ob0 /D _MBCS /D WIN32 /D _WINDOWS /D GTEST_LINKED_AS_SHARED_LIBRARY=1 /D \"CMAKE_INTDIR=\\\"Debug\\\"\" /EHsc /RTC1 /MDd /GS /fp:precise /std:c++17 /Fo\"acceptance_test.dir\\Debug\\\\\" /Fd\"acceptance_test.dir\\Debug\\vc143.pdb\" /external:W0 /Gd /TP /errorReport:queue  /external:I \"D:/!dev/WIP/tools/toolchain/compiledb4ms/build/vcpkg_installed/x64-windows/include\" \"D:\\!dev\\WIP\\tools\\toolchain\\compiledb4ms\\tests\\usage.cpp\"",
		},
		{
			std::filesystem::current_path() / "libcompiledb4ms",
			"D:\\!dev\\WIP\\tools\\toolchain\\compiledb4ms\\tests\\usage.cpp",
			"\"D:\\Program Files\\Microsoft Visual Studio\\2022\\Enterprise\\VC\\Tools\\MSVC\\14.43.34808\\bin\\Hostx64\\x64\\cl.exe\" /c /I\"D:\\!dev\\WIP\\tools\\toolchain\\compiledb4ms\" /Zi /nologo /W1 /WX- /diagnostics:column /Od /Ob0 /D _MBCS /D WIN32 /D _WINDOWS /D GTEST_LINKED_AS_SHARED_LIBRARY=1 /D \"CMAKE_INTDIR=\\\"Debug\\\"\" /EHsc /RTC1 /MDd /GS /fp:precise /std:c++17 /Fo\"acceptance_test.dir\\Debug\\\\\" /Fd\"acceptance_test.dir\\Debug\\vc143.pdb\" /external:W0 /Gd /TP /errorReport:queue  /external:I \"D:/!dev/WIP/tools/toolchain/compiledb4ms/build/vcpkg_installed/x64-windows/include\" \"D:\\!dev\\WIP\\tools\\toolchain\\compiledb4ms\\tests\\usage.cpp\"",
		}
	};
	ASSERT_EQ(sln.command_objects(), expected);
}
