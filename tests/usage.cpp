#include <gtest/gtest.h>

#include <stdlib.h>

#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>

namespace fs = std::filesystem;

std::string read_file(const fs::path& path)
{
	std::ifstream in{ path };
	std::ostringstream os;
	os << in.rdbuf();
	return os.str();
}

std::string get_env(const char* name, const char* default_value)
{
	size_t required_size = 0;
	if (getenv_s(&required_size, nullptr, 0, name)) {
		return default_value;
	}

	std::string env;
	env.resize(required_size - 1);

	getenv_s(&required_size, env.data(), required_size, name);
	return env;

}

TEST(Usage, generate_compiledb_for_vcxproj)
{
	std::string compiledb4ms = get_env("compiledb4ms", "compiledb4ms");
	int exit_code = system(compiledb4ms.c_str());
	ASSERT_EQ(0, exit_code);

	auto res = read_file("compile_commands.json");
	std::string expected = R"([
{
  "directory": "D:/!dev/WIP/tools/toolchain/compiledb4ms/build",
  "file": "D:/!dev/WIP/tools/toolchain/compiledb4ms/tests/usage.cpp",
  "arguments": [
    "D:/Program Files/Microsoft Visual Studio/2022/Enterprise/VC/Tools/MSVC/14.43.34808/bin/HostX64/x64/CL.exe",
    "/std:c++17",
    "/external:I",
    "D:/!dev/WIP/tools/toolchain/compiledb4ms/build/vcpkg_installed/x64-windows/include",
    "D:/!dev/WIP/tools/toolchain/compiledb4ms/tests/usage.cpp"
  ]
}
])";
	ASSERT_EQ(res, expected);
// original
// D:\Program Files\Microsoft Visual Studio\2022\Enterprise\VC\Tools\MSVC\14.43.34808\bin\HostX64\x64\CL.exe /c /Zi /nologo /W4 /WX /diagnostics:column /Od /Ob0 /D _MBCS /D WIN32 /D _WINDOWS /D GTEST_LINKED_AS_SHARED_LIBRARY=1 /D "CMAKE_INTDIR=\"Debug\"" /EHsc /RTC1 /MDd /GS /fp:precise /std:c++17 /Fo"acceptance_test.dir\Debug\\" /Fd"acceptance_test.dir\Debug\vc143.pdb" /external:W0 /Gd /TP /errorReport:queue  /external:I "D:/!dev/WIP/tools/toolchain/compiledb4ms/build/vcpkg_installed/x64-windows/include" "D:\!dev\WIP\tools\toolchain\compiledb4ms\tests\usage.cpp"
}
