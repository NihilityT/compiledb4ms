#ifndef __libutils_utils_h__
#define __libutils_utils_h__

#include <filesystem>
#include <string>
#include <string_view>

namespace utils {

std::string read_file(const std::filesystem::path& path);

std::string get_env(const char* name, std::string_view default_value = "");

}

#endif // __libutils_utils_h__
