#include <libcompiledb4ms/command_object.h>
#include <libcompiledb4ms/utils.h>
#include <libcompiledb4ms/sln.h>
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

	int out_count = 0;
	auto out_objects = [&](auto&& command_objects) {
		for (auto& obj : command_objects) {
			if (out_count++) {
				out << ",\n";
			}
			out << obj;
		}
	};

	std::string_view arch_type;

	out << "[\n";
	for (int i = 1; i < argc; i += 2) {
		if (argv[i] == "-t"sv) {
			arch_type = argv[i + 1];
		} else if (argv[i] == "-p"sv) {
			Vcxproj proj = arch_type.empty()
				? Vcxproj{ argv[i + 1] }
				: Vcxproj{ argv[i + 1], arch_type };
			out_objects(proj.command_objects());
		} else if (argv[i] == "-s"sv) {
			Sln sln = arch_type.empty()
				? Sln{ argv[i + 1] }
				: Sln{ argv[i + 1], arch_type };
			out_objects(sln.command_objects());
		}
	}
	out << "\n]";

	return 0;
}



