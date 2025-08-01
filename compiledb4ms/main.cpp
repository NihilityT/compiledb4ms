#include <libcompiledb4ms/command_object.h>
#include <libcompiledb4ms/utils.h>
#include <libcompiledb4ms/vcxproj.h>

#include <fstream>
#include <string_view>

using namespace compiledb4ms;
using namespace std::literals;

int main(int argc, char* argv[])
{
	if (argc == 1 || argc % 2 != 1) {
		// todo: help
		return -1;
	}

	std::ofstream out{ "compile_commands.json" };
	out << "[\n";
	for (int i = 1; i < argc; i += 2) {
		if (i > 1) {
			out << ",\n";
		}

		if (argv[i] == "-p"sv) {
			Vcxproj proj{ argv[i + 1] };
			for (auto& obj : proj.command_objects()) {
				out << obj;
			}
		}
	}
	out << "\n]";

	return 0;
}



