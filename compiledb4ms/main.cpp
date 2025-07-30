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
			R"("D:\Program Files\Microsoft Visual Studio\2022\Enterprise\VC\Tools\MSVC\14.43.34808\bin\HostX64\x64\CL.exe" )"
			R"(/c /Zi /nologo /W4 /WX /diagnostics:column /Od /Ob0 )"
			+ proj.preprocessor_definitions() + " "
			R"(/EHsc /RTC1 /MDd /GS /fp:precise )"
			+ proj.std() + " "
			R"(/Fo"acceptance_test.dir\Debug\\" )"
			R"(/Fd"acceptance_test.dir\Debug\vc143.pdb" /external:W0 /Gd /TP /errorReport:queue )"
			" " + proj.additional_options() + " "
			"\"" + cl_compile_file.string() + '"',
		};

		out << obj.str();
	}
	out << "\n]";


	return 0;
}



