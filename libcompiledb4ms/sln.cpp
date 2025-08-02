#include <libcompiledb4ms/sln.h>
#include <libcompiledb4ms/vcxproj.h>
#include <libutils/utils.h>

#include <iterator>
#include <regex>
#include <sstream>
#include <string>

namespace compiledb4ms {

Sln::Sln(const std::filesystem::path& path, std::string_view arch)
	: m_sln_path(std::filesystem::absolute(path))
	, m_arch(arch)
{
}

std::unordered_map<std::string, std::filesystem::path> Sln::projects() const
{
	const std::regex reg{ R"regex(Project\([^)]+\)\s*=\s*"([^"]+)"[^"]+"([^"]+))regex" };

	std::unordered_map<std::string, std::filesystem::path> res;
	std::filesystem::path base = m_sln_path.parent_path();

	std::istringstream ss{ utils::read_file(m_sln_path) };
	std::string line;
	while (std::getline(ss, line)) {
		std::smatch sm;
		if (std::regex_search(line, sm, reg)) {
			res[sm[1].str()] = base / sm[2].str();
		}
	}

	return res;
}

std::vector<Command_object> Sln::command_objects() const
{
	std::vector<Command_object> res;
	for (auto& it : projects()) {
		Vcxproj proj{ it.second, m_arch };
		auto objs = proj.command_objects();
		res.insert(res.cend(),
			   std::make_move_iterator(objs.cbegin()),
			   std::make_move_iterator(objs.cend()));
	}
	return res;
}

}
