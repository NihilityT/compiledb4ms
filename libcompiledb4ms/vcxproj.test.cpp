#include <gtest/gtest.h>
#include <vector>

#include <libcompiledb4ms/vcxproj.h>

using namespace compiledb4ms;

TEST(Vcxproj, extract_cl_compile_file_from_vcxproj_file)
{
	Vcxproj proj{ "libcompiledb4ms/vcxproj.test.vcxproj" };

	std::vector<std::filesystem::path> expected{
		"D:\\!dev\\WIP\\tools\\toolchain\\compiledb4ms\\tests\\usage.cpp"
	};
	ASSERT_EQ(proj.cl_compile_files(), expected);
}
