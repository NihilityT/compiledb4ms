#include <fstream>
#include <string>

int main()
{
	std::string expected = R"([
{
  "directory": "D:/!dev/WIP/tools/toolchain/compiledb4ms/build",
  "file": "D:/!dev/WIP/tools/toolchain/compiledb4ms/tests/usage.cpp",
  "arguments": [
    "D:/Program Files/Microsoft Visual Studio/2022/Enterprise/VC/Tools/MSVC/14.43.34808/bin/HostX64/x64/CL.exe",
    "/std:c++17",
    "/external:I","D:/!dev/WIP/tools/toolchain/compiledb4ms/build/vcpkg_installed/x64-windows/include",
    "D:/!dev/WIP/tools/toolchain/compiledb4ms/tests/usage.cpp"
  ]
}
])";
	std::ofstream out{ "compile_commands.json" };
	out << expected;
	return 0;
}



