#include <libcompiledb4ms/command_object.h>
#include <libcompiledb4ms/vcxproj.h>

#include <fstream>

using namespace compiledb4ms;

int main()
{
	Vcxproj proj{ "tests/usage.vcxproj" };

	std::ofstream out{ "compile_commands.json" };
	out << "[\n";
	for (auto& cl_compile_file : proj.cl_compile_files()) {
		Command_object obj = {
			"D:/!dev/WIP/tools/toolchain/compiledb4ms/build",
			cl_compile_file,
			R"("D:\Program Files\Microsoft Visual Studio\2022\Enterprise\VC\Tools\MSVC\14.43.34808\bin\HostX64\x64\CL.exe" /c /Zi /nologo /W4 /WX /diagnostics:column /Od /Ob0 /D _MBCS /D WIN32 /D _WINDOWS /D GTEST_LINKED_AS_SHARED_LIBRARY=1 /D "CMAKE_INTDIR=\"Debug\"" /EHsc /RTC1 /MDd /GS /fp:precise /std:c++17 /Fo"acceptance_test.dir\Debug\\" /Fd"acceptance_test.dir\Debug\vc143.pdb" /external:W0 /Gd /TP /errorReport:queue  /external:I "D:/!dev/WIP/tools/toolchain/compiledb4ms/build/vcpkg_installed/x64-windows/include" "D:\!dev\WIP\tools\toolchain\compiledb4ms\tests\usage.cpp")",
		};
		out << obj.str();
	}
	out << "\n]";


	return 0;
}



