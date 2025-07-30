#include <libutils/utils.h>

#include <fstream>
#include <sstream>

namespace utils {

std::string read_file(const std::filesystem::path& path)
{
	std::ifstream in{ path };
	std::ostringstream os;
	os << in.rdbuf();
	return os.str();
}

std::string get_env(const char* name, std::string_view default_value)
{
	size_t required_size = 0;
	if (getenv_s(&required_size, nullptr, 0, name)
		|| required_size == 0) {
		return std::string(default_value);
	}

	std::string env;
	env.resize(required_size - 1);

	getenv_s(&required_size, env.data(), required_size, name);
	return env;

}

}
