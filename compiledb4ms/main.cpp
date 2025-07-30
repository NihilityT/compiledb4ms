#include <compiledb4ms/command_object.h>

#include <fstream>
#include <string>

int main()
{
	Command_object obj = {
		"D:/!dev/WIP/tools/toolchain/compiledb4ms/build",
		"D:/!dev/WIP/tools/toolchain/compiledb4ms/tests/usage.cpp",
		R"("D:\Program Files\Microsoft Visual Studio\2022\Enterprise\VC\Tools\MSVC\14.43.34808\bin\HostX64\x64\CL.exe" /c /Zi /nologo /W4 /WX /diagnostics:column /Od /Ob0 /D _MBCS /D WIN32 /D _WINDOWS /D GTEST_LINKED_AS_SHARED_LIBRARY=1 /D "CMAKE_INTDIR=\"Debug\"" /EHsc /RTC1 /MDd /GS /fp:precise /std:c++17 /Fo"acceptance_test.dir\Debug\\" /Fd"acceptance_test.dir\Debug\vc143.pdb" /external:W0 /Gd /TP /errorReport:queue  /external:I "D:/!dev/WIP/tools/toolchain/compiledb4ms/build/vcpkg_installed/x64-windows/include" "D:\!dev\WIP\tools\toolchain\compiledb4ms\tests\usage.cpp")",
	};

	std::string expected = "[\n" + obj.str() + "\n]";
	std::ofstream out{ "compile_commands.json" };
	out << expected;
	return 0;
}



