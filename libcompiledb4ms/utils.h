#ifndef __libcompiledb4ms_utils_h__
#define __libcompiledb4ms_utils_h__

#include <filesystem>
#include <string>
#include <unordered_map>

namespace compiledb4ms {
namespace utils {

class Environment {
public:
	std::string get(const std::string& name, std::string_view default_value = "");
	void set(std::unordered_map<std::string, std::string> environments);
private:
	std::unordered_map<std::string, std::string> m_environments;
};

Environment& get_environment();

std::filesystem::path get_cl_path();

}
}

#endif // __libcompiledb4ms_utils_h__
