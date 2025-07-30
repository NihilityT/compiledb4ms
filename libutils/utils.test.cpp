#include <gtest/gtest.h>
#include <libutils/utils.h>

using namespace utils;

TEST(Utils, read_file)
{
	std::string content = read_file("./libutils/utils.test.txt");
	ASSERT_EQ("123", content);
}
