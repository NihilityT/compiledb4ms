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
			proj.directory(),
			cl_compile_file,
			R"("D:\Program Files\Microsoft Visual Studio\2022\Enterprise\VC\Tools\MSVC\14.43.34808\bin\HostX64\x64\CL.exe" )"
			R"(/c )"
			+ proj.debug_information_format() + " "
			+ proj.suppress_startup_banner() + " "
			+ proj.warning_level() + " "
			+ proj.treat_warnings_as_errors() + " "
			+ proj.diagnostics_format() + " "
			+ proj.optimization() + " "
			+ proj.inline_function_expansion() + " "
			+ proj.preprocessor_definitions() + " "
			+ proj.exception_handling() + " "
			+ proj.basic_runtime_checks() + " "
			+ proj.runtime_library() + " "
			+ proj.security_check() + " "
			+ proj.floating_point_model() + " "
			+ proj.std() + " "
			R"(/Fo"acceptance_test.dir\Debug\\" )"
			R"(/Fd"acceptance_test.dir\Debug\vc143.pdb" )"
			+ proj.external_header_warning_level() + " "
			+ proj.calling_convension() + " "
			+ proj.compile_as() + " "
			+ proj.internal_compiler_error_reporting() + " "
			" " + proj.additional_options() + " "
			"\"" + cl_compile_file.string() + '"',
		};

		out << obj.str();
	}
	out << "\n]";


	return 0;
}



