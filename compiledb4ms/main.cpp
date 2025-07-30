#include <compiledb4ms/command_object.h>

#include <fstream>
#include <string>

int main()
{
	Command_object obj = {
		"D:/!dev/WIP/tools/toolchain/compiledb4ms/build",
		"D:/!dev/WIP/tools/toolchain/compiledb4ms/tests/usage.cpp",
		{
			"D:/Program Files/Microsoft Visual Studio/2022/Enterprise/VC/Tools/MSVC/14.43.34808/bin/HostX64/x64/CL.exe",
			"/std:c++17",
			"/external:I",
			"D:/!dev/WIP/tools/toolchain/compiledb4ms/build/vcpkg_installed/x64-windows/include",
			"D:/!dev/WIP/tools/toolchain/compiledb4ms/tests/usage.cpp"
		}
	};
	std::string expected = "[\n" + obj.str() + "\n]";
	std::ofstream out{ "compile_commands.json" };
	out << expected;
	return 0;
}



