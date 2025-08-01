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

	std::string_view arch_type;
	int out_count = 0;

	std::ofstream out{ "compile_commands.json" };
	out << "[\n";
	for (int i = 1; i < argc; i += 2) {
		if (argv[i] == "-t"sv) {
			arch_type = argv[i + 1];
		} else if (argv[i] == "-p"sv) {
			Vcxproj proj = arch_type.empty()
				? Vcxproj{ argv[i + 1] }
				: Vcxproj{ argv[i + 1], arch_type };
			for (auto& obj : proj.command_objects()) {
				if (out_count++) {
					out << ",\n";
				}
				out << obj;
			}
		}
	}
	out << "\n]";

	return 0;
}



