#include <libcompiledb4ms/command_object.h>
#include <libcompiledb4ms/utils.h>
#include <libcompiledb4ms/vcxproj.h>

#include <fstream>

using namespace compiledb4ms;

int main()
{
	Vcxproj proj{ "tests/usage.vcxproj" };

	std::ofstream out{ "compile_commands.json" };
	out << "[\n";
	for (auto& obj : proj.command_objects()) {
		out << obj;
	}
	out << "\n]";


	return 0;
}



