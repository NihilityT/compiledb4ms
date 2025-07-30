#ifndef __libutils_utils_h__
#define __libutils_utils_h__

#include <filesystem>
#include <string>
#include <string_view>
#include <vector>

namespace utils {

std::string read_file(const std::filesystem::path& path);

std::string get_env(const char* name, std::string_view default_value = "");

std::vector<std::string> split(const std::string& str, char delimiter = ';');

void replace(std::string& str, std::string_view substr, std::string_view replacement);

}

#endif // __libutils_utils_h__
