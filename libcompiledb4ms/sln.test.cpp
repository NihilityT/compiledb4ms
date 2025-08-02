#include <filesystem>
#include <gtest/gtest.h>

#include <libcompiledb4ms/sln.h>
#include <string>
#include <unordered_map>

using namespace compiledb4ms;

TEST(libcompiledb4ms_Sln, get_project_filepaths)
{
	std::filesystem::path base = std::filesystem::absolute("libcompiledb4ms");
	Sln sln{ base / "sln.test.sln" };

	std::unordered_map<std::string, std::filesystem::path> expected{
		{ "test", base / "vcxproj.test.vcxproj" },
	};
	ASSERT_EQ(sln.projects(), expected);
}
